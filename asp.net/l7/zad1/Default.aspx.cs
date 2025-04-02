using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad1
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string loggedInUser = System.Security.Principal.WindowsIdentity.GetCurrent().Name;

            lblLoggedInUser.Text = "Zalogowany użytkownik: " + loggedInUser;
        }
    }
}