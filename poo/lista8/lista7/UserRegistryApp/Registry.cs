using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace aggregator
{
    public partial class Registry : Form
    {
        UserRegistry _userRegistry = UserRegistry.GetInstance();
        EventAggregator _eventAggregator = EventAggregator.GetInstance();
        UserData chosenUser;

        public Registry()
        {
            InitializeComponent();

            button1.Visible = false;
            listView1.Columns.Add("Name");
            listView1.Columns.Add("Surname");
            listView1.Columns.Add("Birthdate");
            listView1.Columns.Add("Address");
            _eventAggregator.AddSubscriber<CategorySelectedNotification>(notification => PopulateUserList(notification.SelectedCategory));
            _eventAggregator.AddSubscriber<UserProfileSelectedNotification>(notification => {
                string[] nameParts = notification.SelectedUser.Split(' ');

                UserData dbUser = _userRegistry.GetUser(nameParts[0], nameParts[1]);
                chosenUser = dbUser;
                PopulateUserList("", chosenUser);

            });
            _eventAggregator.AddSubscriber<AddUserNotification>(notification => PopulateTreeView());
            _eventAggregator.AddSubscriber<EditUserNotification>(notification => {
                chosenUser = notification.UserToEdit;
                PopulateUserList("", notification.UserToEdit);
                PopulateTreeView();
            });
        }

        private void PopulateTreeView()
        {
            treeView1.Nodes.Clear();
            List<string> categories = _userRegistry.GetCategories();

            foreach (string category in categories)
            {
                List<UserData> users = _userRegistry.GetUsersFromCategory(category);
                TreeNode tn = treeView1.Nodes.Add(category);
                tn.Tag = "Category";
                foreach (UserData user in users)
                {
                    TreeNode userNode = tn.Nodes.Add(string.Format("{0} {1}", user.Name, user.Surname));
                    userNode.Tag = "User";
                }
                tn.Expand();
            }
        }

        private void PopulateUserList(string category, UserData dbUser = null)
        {
            if (dbUser == null && category.Equals(""))
            {
                throw new ArgumentException("you need to pass either category or user data");
            }
            listView1.Items.Clear();
;

            listView1.View = View.Details;

            if (dbUser == null)
            {
                button1.Visible = false;

                List<UserData> users = _userRegistry.GetUsersFromCategory(category);

                foreach (UserData user in users)
                {
                    ListViewItem item = new ListViewItem(user.Name);
                    item.SubItems.Add(user.Surname);
                    item.SubItems.Add(user.Birthdate);
                    item.SubItems.Add(user.Address);

                    listView1.Items.Add(item);
                }
            } else
            {
                button1.Visible = true;

                if (dbUser != null)
                {
                    ListViewItem item = new ListViewItem(dbUser.Name);
                    item.SubItems.Add(dbUser.Surname);
                    item.SubItems.Add(dbUser.Birthdate);
                    item.SubItems.Add(dbUser.Address);

                    listView1.Items.Add(item);
                }
            }
        }


        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Tag != null && (string)e.Node.Tag == "Category")
            {
                string selectedCategory = e.Node.Text;

                CategorySelectedNotification category = new CategorySelectedNotification
                {
                    SelectedCategory = selectedCategory
                };

                _eventAggregator.Publish(category);

            } else if (e.Node.Tag != null && (string)e.Node.Tag == "User")
            {
                string username = e.Node.Text;

                UserProfileSelectedNotification profile = new UserProfileSelectedNotification
                {
                    SelectedUser = username
                };

                _eventAggregator.Publish(profile);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            AddEditRow editUserForm = new AddEditRow(chosenUser);
            editUserForm.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            AddEditRow addUserForm = new AddEditRow();
            addUserForm.ShowDialog();
        }
    }
}
