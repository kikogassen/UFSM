using Newtonsoft.Json.Linq;
using System;
using System.IO;
using System.Linq;
using System.Text;

namespace UFSM.LME.Json.Helpers
{
    public static class HtmlHelper
    {
        public static void CreateHtmlLibrary(string basePath, JObject jObject)
        {
            CreateLibreImage(basePath);

            var indexHtml = new StringBuilder();
            var indexTemplate = EmbbedResourceHelper.ReadEmbbedResourceString("UFSM.LME.Json.Resources.IndexTemplate.html");

            var topics = ((JArray)jObject["topicMap"]["topic"]).Where(x => x["instanceOf"] != null);
            var movies = topics.Where(topic => topic["instanceOf"]["topicRef"]["@href"].ToString() == "#Filme");
            var associations = (JArray)jObject["topicMap"]["association"];

            foreach (var topic in movies)
            {
                var currentFile = $"{topic["@id"]}.html";
                var movieHtml = GetHtmlForMovie(jObject, topic);

                using (var writer = new StreamWriter(Path.Combine(basePath, currentFile)))
                {
                    writer.Write(movieHtml);
                }

                indexHtml.Append($"<li><a href='{currentFile}'>{topic["baseName"]["baseNameString"]}</a></li>");
            }

            foreach (var topic in topics.Except(movies))
            {
                var currentFile = $"{topic["@id"]}.html";
                var movieHtml = GetHtmlForMovie(jObject, topic);

                using (var writer = new StreamWriter(Path.Combine(basePath, currentFile)))
                {
                    writer.Write(movieHtml);
                }
            }

            using (var writer = new StreamWriter(Path.Combine(basePath, "_index.html")))
            {
                writer.Write(indexTemplate.Replace("{MOVIE_LIST}", indexHtml.ToString()));
            }
        }

        private static void CreateLibreImage(string basePath)
        {
            var libreImage = EmbbedResourceHelper.ReadEmbbedResourceBinary("UFSM.LME.Json.Resources.libre.png");
            var libreImagePath = Path.Combine(basePath, "_libre.png");

            if (File.Exists(libreImagePath))
            {
                File.Delete(libreImagePath);
            }

            using (var writer = new FileStream(libreImagePath, FileMode.CreateNew))
            {
                writer.Write(libreImage, 0, Convert.ToInt32(libreImage.Length));
            }
        }

        private static string GetHtmlForMovie(JObject jObject, JToken movie)
        {
            var subpageTemplate = EmbbedResourceHelper.ReadEmbbedResourceString("UFSM.LME.Json.Resources.SubpageTemplate.html");
            var occurrencesHtml = GetOccurrencesForMovie(movie);
            var associationsHtml = GetAssociationsForMovie(jObject, movie);

            return subpageTemplate.Replace("{SUBPAGE_INFO}", $@"<h1>{movie["baseName"]["baseNameString"]}<h1>{ associationsHtml.ToString()}{ occurrencesHtml.ToString()}");
        }

        private static string GetAssociationsForMovie(JObject jObject, JToken movie)
        {
            StringBuilder associationsHtml = null;
            var associations = (JArray)jObject["topicMap"]["association"];
            var topics = ((JArray)jObject["topicMap"]["topic"]).Where(x => x["instanceOf"] != null);

            var movieId =  $"#{movie["@id"].ToString()}";

            var movieAssociations = associations
                .Where(association => association["member"].Any(member => FixAssociationId(member["topicRef"]["@href"].ToString()) == movieId))
                .OrderBy(association => association["instanceOf"]["topicRef"]["@href"].ToString());

            string lastAssociationId = null;
            foreach (var association in movieAssociations)
            {
                if(associationsHtml == null)
                {
                    associationsHtml = new StringBuilder("<h2>Associações</h2>");
                }

                var associationId = association["instanceOf"]["topicRef"]["@href"].ToString();

                var memberId = FixAssociationId(association["member"]
                    .First(member => FixAssociationId(member["topicRef"]["@href"].ToString()) != movieId)
                    ["topicRef"]["@href"]
                    .ToString());

                var memberName = topics
                    .First(topic => topic["@id"].ToString() == memberId.Substring(1))
                    ["baseName"]["baseNameString"];

                if (lastAssociationId != associationId)
                {
                    associationsHtml.AppendLine($"<h3>{associationId}</h3>");
                }
                lastAssociationId = associationId;

                associationsHtml.AppendLine($"<p><a href='./{memberId.Substring(1)}.html'>{memberName}</a></p>");
            }

            return associationsHtml?.ToString() ?? string.Empty;
        }

        private static string GetOccurrencesForMovie(JToken movie)
        {
            var occurrences = movie["occurrence"];
            StringBuilder occurrencesHtml = new StringBuilder();

            if (occurrences == null)
            {
            }
            else if (occurrences is JArray)
            {
                var movies = (JArray)movie["occurrence"];
                var types = new string[] { "scope", "instanceOf" };

                foreach (var type in types)
                {
                    var occurencesOfType = movies
                        .Where(occurrence => occurrence[type] != null)
                        .OrderBy(x => x[type]["topicRef"]["@href"].ToString());

                    string lastOccurrenceId = null;
                    foreach (var occurrence in occurencesOfType)
                    {
                        var currentOccurenceId = occurrence[type]["topicRef"]["@href"].ToString();

                        if (lastOccurrenceId != currentOccurenceId)
                        {
                            occurrencesHtml.AppendLine($"<h3>{currentOccurenceId}</h3>");
                        }

                        lastOccurrenceId = currentOccurenceId;

                        occurrencesHtml.AppendLine(GetHtmlForOccurrence(occurrence, type));
                    }
                }
            }
            else if (occurrences["scope"] != null)
            {
                occurrencesHtml.AppendLine($"<h3>{occurrences["scope"]["topicRef"]["@href"].ToString()}</h3>");
                occurrencesHtml.AppendLine(GetHtmlForOccurrence(occurrences, "scope"));
            }
            else if (occurrences["instanceOf"] != null)
            {
                occurrencesHtml.AppendLine($"<h3>{occurrences["instanceOf"]["topicRef"]["@href"].ToString()}</h3>");
                occurrencesHtml.AppendLine(GetHtmlForOccurrence(occurrences, "instanceOf"));
            }

            if(occurrencesHtml.Length == 0)
            {
                return string.Empty;
            }

            return "<h2>Ocorrências</h2>\n" + occurrencesHtml.ToString();
        }

        private static string GetHtmlForOccurrence(JToken occurrence, string type)
        {
            var currentOccurenceId = occurrence[type]["topicRef"]["@href"].ToString();

            var content = type == "instanceOf" ?
                occurrence["resourceRef"]["@href"] :
                occurrence["resourceData"];

            return currentOccurenceId.Contains("site") ?
                $"<p><a href='{content}'>{content}</a></p>\n" :
                $"<p>{content}</p>\n";
        }

        private static string FixAssociationId(string associationId)
        {
            return associationId
                .Replace(",", "")
                .Replace("º", "");
        }
    }
}
