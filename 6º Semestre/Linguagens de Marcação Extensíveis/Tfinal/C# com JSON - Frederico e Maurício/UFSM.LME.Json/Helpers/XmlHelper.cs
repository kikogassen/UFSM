using Newtonsoft.Json;
using System.Xml;

namespace UFSM.LME.Json.Helpers
{
    public static class XmlHelper
    {
        public static string ConvertToJson(string xml)
        {
            var document = new XmlDocument();

            document.LoadXml(xml);

            return JsonConvert.SerializeXmlNode(document, Newtonsoft.Json.Formatting.Indented);
        }
    }
}
