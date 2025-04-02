using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication2
{
    public partial class About : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            //Response.Write($"supports cookies: {CheckSessionCookieSupport()}");

            int i = 2;
            if (i == 0)
            {
                HttpCookie cookie = new HttpCookie("cookie", "cookie");
                cookie.Expires = DateTime.Now.AddHours(1);

                Response.Cookies.Add(cookie);
            }
            else if (i == 1)
            {
                if (Request.Cookies["cookie"] != null)
                {
                    string cookieValue = Request.Cookies["cookie"].Value;
                    Response.Write($"cookie value: {cookieValue}");
                }
            }
            else if (i == 2)
            {
                HttpCookie myCookieToRemove = new HttpCookie("cookie");
                myCookieToRemove.Expires = DateTime.Now.AddDays(-1);

                Response.Cookies.Add(myCookieToRemove);
            }
            zad3();
        }

        private Boolean CheckSessionCookieSupport()
        {
            Response.Write("Session Supports Cookies = " + Request.Browser.Cookies + "<br>");
            if (Request.QueryString["TestingCookie"] == null)
            {
                HttpCookie cookie = new HttpCookie("CookieTest", "");
                Response.Cookies.Add(cookie);

                Response.Redirect("About.aspx?TestingCookie=1");
                return false;
            }
            else
            {
                return Request.Cookies["CookieTest"] != null;
            }
        }

        private void zad3()
        {
            string host = Request.Headers["Host"];
            Response.Write($"<br>Host: {host}<br>");

            Response.Headers.Add("myheader", "myheader");

            string relativePath = "~/Content/enzo.jpg";
            string physicalPath = Server.MapPath(relativePath);
            Response.Write($"Physical Path: {physicalPath}<br>");


            HttpContext context = HttpContext.Current;
            Response.Write("<p>HttpContext.Current Example:</p>");

            context.AddError(new Exception("New Exception #1"));
            context.AddError(new Exception("New Exception #2"));
            context.AddError(new Exception("New Exception #3"));

            Exception[] errs = context.AllErrors;

            foreach (Exception ex in errs)
            {
                Response.Write("<p>" + Server.HtmlEncode(ex.ToString()) + "</p>");
            }
            context.ClearError();

        }
    }
}