using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static HttpClient client = new HttpClient();
        static Program()
        {
            client.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));
        }
        static void Main(string[] args)
        {
            Get();
            Post();
            Console.ReadLine();
        }
        async static Task Get()
        {
            var responseString = await client.GetStringAsync("http://localhost:5153/Persons");

            var response = JsonConvert.DeserializeObject<IEnumerable<Person>>(responseString);
            foreach (var person in response)
            {
                Console.WriteLine(string.Format("{0} {1}", person.Name, person.Age))
               ;
            }
        }
        async static Task Post()
        {
            var person = new Person() { Name = "ghj", Age = 18 };
            var request = JsonConvert.SerializeObject(person);
            StringContent content = new StringContent(request, Encoding.UTF8, "application/json");
            var response = await client.PostAsync("http://localhost:5153/Persons", content);
            var responseString = await response.Content.ReadAsStringAsync();
            var personResp = JsonConvert.DeserializeObject<Person>(responseString);
            Console.WriteLine(string.Format("{0} {1}", personResp.Name, personResp.Age));
        }
    }
}
public class Person
{
    public int Id { get; set; }

    public string Name { get; set; }
    public int Age { get; set; }
}