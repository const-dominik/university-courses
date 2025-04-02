using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Xml.Linq;

namespace aggregator
{
    public class UserData
    {
        public string Name { get; set; }
        public string Surname { get; set; }
        public string Address { get; set; }
        public string Birthdate { get; set; }
        public string Category { get; set; }
    }

    public class CategorySelectedNotification
    {
        public string SelectedCategory { get; set; }
    }

    public class UserProfileSelectedNotification
    {
        public string SelectedUser { get; set; }
    }

    public class AddUserNotification
    {
        public UserData UserToAdd { get; set; }
    }

    public class EditUserNotification
    {
        public UserData UserToEdit { get; set; }
        public UserData UserAfterEdit { get; set; }
    }


    public class UserRegistry
    {
        private static readonly UserRegistry _instance = new UserRegistry();
        private readonly List<UserData> _users = new List<UserData>();
        private readonly EventAggregator _eventAggregator = EventAggregator.GetInstance();

        public UserRegistry()
        {
            _eventAggregator.AddSubscriber<AddUserNotification>(notification =>
                AddUser(notification.UserToAdd)
            );
            _eventAggregator.AddSubscriber<EditUserNotification>(notification =>
                EditUser(notification.UserToEdit, notification.UserAfterEdit)
            );
        }

        public static UserRegistry GetInstance()
        {
            return _instance;
        }

        public void AddUser(UserData user)
        {
            if (GetUser(user.Name, user.Surname) == null)
            {
                _users.Add(user);
            } else
            {
                EditUser(user, user);
            }
        }

        public void EditUser(UserData user, UserData userAfterEdit)
        {
            int index = _users.FindIndex(u => u.Name == user.Name && u.Surname == user.Surname);
            _users[index].Address = userAfterEdit.Address;
            _users[index].Name = userAfterEdit.Name;
            _users[index].Surname = userAfterEdit.Surname;
            _users[index].Birthdate = userAfterEdit.Birthdate;   
            _users[index].Category = userAfterEdit.Category;
        }

        public UserData GetUser(string name, string surname)
        {
            foreach (UserData user in _users)
            {
                if (user.Name.Equals(name) && user.Surname.Equals(surname))
                {
                    return user;
                }
            }

            return null;
        }

        public List<string> GetCategories()
        {
            List<string> categories = new List<string>();
            foreach (UserData userData in _users)
            {
                if (!categories.Contains(userData.Category))
                    categories.Add(userData.Category);
            }
            return categories;
        }

        public List<UserData> GetUsersFromCategory(string category)
        {
            List<UserData> users = new List<UserData>();
            foreach (UserData userData in _users)
            {
                if (userData.Category.Equals(category))
                {
                    users.Add(userData);
                }
            }
            return users;
        }
    }

}