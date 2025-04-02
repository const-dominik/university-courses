using System.Collections.Generic;
using System.Data.Entity;
using zad2.Models;

public class ApplicationDbContext : DbContext
{
    public ApplicationDbContext() : base("name=ApplicationDbContext")
    {
    }

    public DbSet<User> Users { get; set; }
    public DbSet<Password> Passwords { get; set; }
}
