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
    public partial class AddEditRow : Form
    {
        EventAggregator _eventAggregator = EventAggregator.GetInstance();
        private UserData _userData;

        public AddEditRow()
        {
            InitializeComponent();
        }

        public AddEditRow(UserData userData)
        {
            InitializeComponent();
            _userData = userData;
            fillForm();
        }

        private void fillForm()
        {
            textBox1.Text = _userData.Name;
            textBox2.Text = _userData.Surname;
            textBox3.Text = _userData.Birthdate;
            textBox4.Text = _userData.Address;
            textBox5.Text = _userData.Category;
        }

       private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.TextLength > 0 && textBox2.TextLength > 0 && textBox3.TextLength > 0 && textBox4.TextLength > 0 && textBox5.TextLength > 0) {
                string name = textBox1.Text;
                string surname = textBox2.Text;
                string birthdate = textBox3.Text;
                string address = textBox4.Text;
                string category = textBox5.Text;

                UserData user = new UserData
                {
                    Name = name,
                    Surname = surname,
                    Birthdate = birthdate,
                    Address = address,
                    Category = category
                };

                if (_userData == null)
                {
                    AddUserNotification notification = new AddUserNotification
                    {
                        UserToAdd = user,
                    };
                    _eventAggregator.Publish(notification);
                } else
                {
                    EditUserNotification notification = new EditUserNotification
                    { 
                        UserToEdit = _userData,
                        UserAfterEdit = user
                    };
                    _eventAggregator.Publish(notification);
                }

                DialogResult = DialogResult.OK;
                Close();
            }
        }
    }
}
