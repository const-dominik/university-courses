using System.Web;
using System.Web.Optimization;

namespace zad2
{
    public class IdentityConfig : Controller
    {
        public static void RegisterRoles(RoleManager<IdentityRole> roleManager)
        {
            // Dodaj role
            roleManager.Create(new IdentityRole("Admin"));
            roleManager.Create(new IdentityRole("User"));
        }
    }
}
