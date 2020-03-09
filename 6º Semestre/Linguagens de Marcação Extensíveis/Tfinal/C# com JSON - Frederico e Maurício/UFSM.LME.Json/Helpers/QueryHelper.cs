using Newtonsoft.Json.Linq;
using System;
using System.Diagnostics;
using System.Linq;

namespace UFSM.LME.Json.Helpers
{
    public static class QueryHelper
    {
        public static void RunQuerys(JObject jObject)
        {
            var stopWatch = new Stopwatch();
            var topics = (JArray)jObject["topicMap"]["topic"];
            var associations = (JArray)jObject["topicMap"]["association"];

            stopWatch.Start();
            // Consulta a)
            var genres = topics
                .Where(topic => topic["instanceOf"]?["topicRef"]?["@href"]?.ToString() == "#Genero")
                .Select(topic => topic["baseName"]["baseNameString"].ToString().Trim())
                .Distinct();

            Console.WriteLine("\n[a] Gêneros sem duplicatas: {0}", string.Join(", ", genres));
            Console.WriteLine("Tempo de execução: {0}ms\n", stopWatch.ElapsedMilliseconds);

            stopWatch.Restart();
            // Consulta b)
            var movies = topics
                .Where(topic => topic["instanceOf"]?["topicRef"]?["@href"]?.ToString() == "#Filme");

            var idsMoviesFrom200 = associations
                .Where(association => association["instanceOf"]?["topicRef"]?["@href"]?.ToString() == "#filme-ano")
                .Where(association => association["member"]?[1]?["topicRef"]?["@href"].ToString() == "#id_2000")
                .Select(association => association["member"]?[0]?["topicRef"]?["@href"]?.ToString().Substring(1));

            var namesMovies2000 = movies
                .Where(movie => idsMoviesFrom200.Contains(movie["@id"].ToString()))
                .Select(movie => movie["baseName"]["baseNameString"].ToString())
                .OrderBy(movieName => movieName);

            Console.WriteLine("\n[b] Filmes de 2000: {0}", string.Join(", ", namesMovies2000));
            Console.WriteLine("Tempo de execução: {0}ms\n", stopWatch.ElapsedMilliseconds);

            stopWatch.Restart();
            // Consulta c)
            var specialSinopse = movies
                .Where(movie =>
                {
                    if (!(movie["occurrence"] is JArray))
                    {
                        // Suportar os casos em que 'occurence' é só um objeto (nenhum deles possui sinopse)
                        return false;
                    }

                    var occurenceArray = (JArray)movie["occurrence"];

                    var sinopse = occurenceArray.FirstOrDefault(occurence => occurence["scope"]?["topicRef"]?["@href"]?.ToString() == "#sinopse");

                    return sinopse["resourceData"].ToString().ToLower().Contains("especial,");
                })
                .Select(topic =>
                {
                    var occurenceArray = (JArray)topic["occurrence"];
                    var sinopse = occurenceArray.FirstOrDefault(occurence => occurence["scope"]?["topicRef"]?["@href"]?.ToString() == "#ingles");

                    return sinopse["resourceData"].ToString();
                });

            Console.WriteLine("\n[c] Título inglês dos que possuem 'especial' na sinopse: {0}", string.Join(", ", specialSinopse));
            Console.WriteLine("Tempo de execução: {0}ms\n", stopWatch.ElapsedMilliseconds);

            stopWatch.Restart();
            // Consulta d)
            var thriller = associations
                .Where(association => association["instanceOf"]?["topicRef"]?["@href"]?.ToString() == "#filme-genero")
                .Where(association => association["member"]?[1]?["topicRef"]?["@href"].ToString() == "#thriller")
                .Select(association => association["member"]?[0]?["topicRef"]?["@href"]?.ToString().Substring(1));

            var siteThriller = movies
               .Where(movie => thriller.Contains(movie["@id"].ToString()))
               .Select(movie =>
               {
                   var occurenceArray = (JArray)movie["occurrence"];
                   var site = occurenceArray.FirstOrDefault(occurence => occurence["instanceOf"]?["topicRef"]?["@href"]?.ToString() == "#site");

                   return site?["resourceRef"]["@href"].ToString() ?? "(null)";
               });

            Console.WriteLine("\n[d] Site dos filmes thriller: {0}", string.Join(", ", siteThriller));
            Console.WriteLine("Tempo de execução: {0}ms\n", stopWatch.ElapsedMilliseconds);

            stopWatch.Restart();
            // Consulta e)
            var amountOfMoviesWithMoreThanThreeSupportCasts = movies
                .Where(movie =>
                {
                    if (!(movie["occurrence"] is JArray))
                    {
                        // Suportar os casos em que 'occurence' é só um objeto (nenhum deles possui elenco de apoio)
                        return false;
                    }

                    var occurenceArray = (JArray)movie["occurrence"];
                    var supportCast = occurenceArray.Where(occurence => occurence["scope"]?["topicRef"]?["@href"]?.ToString() == "#elencoApoio");

                    return supportCast.Count() > 3;
                })
                .Count();

            Console.WriteLine("\n[e] Quantidade de filmes com mais de 3 elenco de apoio: {0}", amountOfMoviesWithMoreThanThreeSupportCasts);
            Console.WriteLine("Tempo de execução: {0}ms\n", stopWatch.ElapsedMilliseconds);

            stopWatch.Restart();
            // Consulta f)
            var moviesWithCastOnSinopse = movies
                .Where(movie =>
                {
                    if (!(movie["occurrence"] is JArray))
                    {
                        // Suportar os casos em que 'occurence' é só um objeto (nenhum deles possui sinopse)
                        return false;
                    }

                    var castNames = associations
                        .Where(association => association["instanceOf"]?["topicRef"]?["@href"]?.ToString() == "#filme-elenco")
                        .Where(association => association["member"]?[0]?["topicRef"]?["@href"].ToString().Substring(1) == movie["@id"].ToString())
                        .Select(association =>
                        {
                            var topicId = association["member"]?[1]?["topicRef"]?["@href"]?.ToString().Substring(1);

                            return topics
                                .First(topic => topicId == topic["@id"].ToString())
                                ["baseName"]["baseNameString"]
                                .ToString();
                        });


                    var occurenceArray = (JArray)movie["occurrence"];
                    var sinopse = occurenceArray.FirstOrDefault(occurence => occurence["scope"]?["topicRef"]?["@href"]?.ToString() == "#sinopse")?.ToString();

                    return castNames.Any(name => sinopse.Contains(name));
                })
                .Select(topic => topic["@id"].ToString());

            Console.WriteLine("\n[f] Filmes que o elenco aparece na sinopse: {0}", string.Join(", ", moviesWithCastOnSinopse));
            Console.WriteLine("Tempo de execução: {0}ms\n", stopWatch.ElapsedMilliseconds);
        }
    }
}
