using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Schema;
using System;
using System.Collections.Generic;
using System.IO;
using UFSM.LME.Json.Helpers;

namespace UFSM.LME.Json
{
    class Program
    {
        private static readonly string OutputPath = "Output";
        private static readonly string HtmlPath = Path.Combine(OutputPath, "HTML");

        static void Main(string[] args)
        {
            if(!Directory.Exists(OutputPath))
            {
                Directory.CreateDirectory(OutputPath);
                Directory.CreateDirectory(HtmlPath);
            }

            CreateJson(out string json, out string schema);

            var jObject = JObject.Parse(json);

            if (!ValidateJson(jObject, schema))
            {
                Console.WriteLine("Erro de validação, saindo do programa.");
                return;
            }

            RunQuerys(jObject);
            GenerateHtml(jObject);

            Console.WriteLine("Pressione qualquer tecla para encerrar o programa.");
            Console.ReadKey();
        }

        private static void CreateJson(out string json, out string schema)
        {
            Console.WriteLine("[*] Lendo arquivo XML de entrada.");
            var xml = EmbbedResourceHelper.ReadEmbbedResourceString("UFSM.LME.Json.Resources.GioMovies.xtm");

            Console.WriteLine("[*] Lendo arquivo JSON Schema de entrada.");
            schema = EmbbedResourceHelper.ReadEmbbedResourceString("UFSM.LME.Json.Resources.GioMoviesSchema.json");

            Console.WriteLine("[*] Convertendo para JSON.");
            json = XmlHelper.ConvertToJson(xml);

            Console.WriteLine("[*] Escrevendo arquivo JSON.");
            using (var writer = new StreamWriter(Path.Combine(OutputPath, "GioMovies.json")))
            {
                writer.WriteLine(json);
            }
        }

        private static bool ValidateJson(JObject jObject, string schema)
        {
            Console.WriteLine("[*] Validando JSON.");
            var jSchema = JSchema.Parse(schema);
            var isValid = jObject.IsValid(jSchema, out IList<string> errorMessages);

            Console.WriteLine("[{0}] Resultado da validação: {1}", isValid ? '+' : '-', isValid ? "Arquivo válido" : "Arquivo inválido");
            if (errorMessages.Count > 0)
            {
                Console.WriteLine("[!] Mensagens de erro:");

                foreach (var errorMessage in errorMessages)
                {
                    Console.WriteLine(errorMessage);
                }
            }

            return isValid;
        }   

        private static void RunQuerys(JObject jObject)
        {
            Console.WriteLine("\n[+] Executando consultas");

            QueryHelper.RunQuerys(jObject);
        }

        private static void GenerateHtml(JObject jObject)
        {
            Console.WriteLine("\n[+] Gerando HTML");

            HtmlHelper.CreateHtmlLibrary(HtmlPath, jObject);

            Console.WriteLine("[+] Sucesso\n");
        }
    }
}
