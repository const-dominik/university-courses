using System;

namespace zad2.Models
{
    public class Password
    {
        public int Id { get; set; }
        public int UserId { get; set; }
        public string Hash { get; set; }
        public DateTime SetDate { get; set; }
    }
}