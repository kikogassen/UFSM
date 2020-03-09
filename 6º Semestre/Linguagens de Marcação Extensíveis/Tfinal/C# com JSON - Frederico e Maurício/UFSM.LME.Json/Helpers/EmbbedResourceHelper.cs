using System;
using System.IO;
using System.Reflection;

namespace UFSM.LME.Json.Helpers
{
    public static class EmbbedResourceHelper
    {
        public static string ReadEmbbedResourceString(string resourceName)
        {
            var assembly = Assembly.GetExecutingAssembly();

            using (var stream = assembly.GetManifestResourceStream(resourceName))
            using (var reader = new StreamReader(stream))
            {
                return reader.ReadToEnd();
            }
        }

        public static byte[] ReadEmbbedResourceBinary(string resourceName)
        {
            using (var stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(resourceName))
            {
                byte[] buffer = new byte[stream.Length];
                stream.Read(buffer, 0, Convert.ToInt32(stream.Length));

                return buffer;
            }
        }
    }
}
