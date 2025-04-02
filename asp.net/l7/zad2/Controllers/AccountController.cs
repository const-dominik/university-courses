using System;
using System.Linq;
using System.Web.Mvc;
using System.Web.Security;
using zad2.Models;
using BCrypt.Net;
using System.EnterpriseServices.CompensatingResourceManager;

public class AccountController : Controller
{
    private readonly ApplicationDbContext _context;

    public AccountController()
    {
        _context = new ApplicationDbContext();
    }

    [HttpGet]
    public ActionResult Register()
    {
        return View();
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public ActionResult Register(RegisterViewModel model)
    {
        if (ModelState.IsValid)
        {

            string hashedPassword = BCrypt.Net.BCrypt.HashPassword(model.Password);

            var newUser = new User
            {
                Username = model.Username,
                Email = model.Email
            };
            _context.Users.Add(newUser);
            _context.SaveChanges();

            var newPassword = new Password
            {
                UserId = newUser.Id,
                Hash = hashedPassword,
                SetDate = DateTime.UtcNow
            };

            _context.Passwords.Add(newPassword);
            _context.SaveChanges();

            return RedirectToAction("Login");
        }

        return View(model);
    }

    [HttpGet]
    [AllowAnonymous]
    public ActionResult Login()
    {
        return View();
    }

    [HttpPost]
    [AllowAnonymous]
    [ValidateAntiForgeryToken]
    public ActionResult Login(LoginViewModel model)
    {
        if (ModelState.IsValid)
        {
            var user = _context.Users.SingleOrDefault(u => u.Username == model.Username);

            if (user != null)
            {
                bool isValidPassword = ValidatePassword(model.Password, user.Id);

                if (isValidPassword)
                {
                    FormsAuthentication.SetAuthCookie(model.Username, false);
                    TempData["UserName"] = user.Username;
                    return RedirectToAction("Index", "Home");
                }
            }

            ModelState.AddModelError("", "Invalid username or password.");
        }

        return View(model);
    }

    [Authorize]
    public ActionResult Logout()
    {
        FormsAuthentication.SignOut();
        return RedirectToAction("Index", "Home");
    }

    private bool ValidatePassword(string enteredPassword, int userId)
    {
        var password = _context.Passwords.SingleOrDefault(u => u.UserId == userId);
        if (password != null) {
            return BCrypt.Net.BCrypt.Verify(enteredPassword, password.Hash);
        }
        return false;
    }
}
