using System;
using System.IO;
using System.Web;

namespace WebApplication1
{
    public class IISHandler1 : IHttpHandler
    {
        public void ProcessRequest(HttpContext context)
        {
            context.Response.Write("adres: " + context.Request.Url);
            context.Response.Write("<br />");
            context.Response.Write("method: " + context.Request.HttpMethod);
            context.Response.Write("<br />");
            context.Response.Write("Headery:");
            foreach (string key in context.Request.Headers)
            {
                context.Response.Write("<br />" + key + ": " + context.Request.Headers[key]);
            }
            if (context.Request.HttpMethod == "POST")
            {

                using (StreamReader reader = new StreamReader(context.Request.InputStream))
                {
                    string requestBody = reader.ReadToEnd();
                    if (requestBody != "")
                    {
                        context.Response.Write("<br />body:" + requestBody);
                    }
                }
            }
        }

        public bool IsReusable
        {
            get { return false; }
        }
    }
}
