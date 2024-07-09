using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1Lab1
{
    public partial class addForm : Form

    {
        private Form1 mainForm;
        int receivedCookID;
        
        SqlConnection connection = new SqlConnection("Data Source=DESKTOP-6NQQME4\\SQLEXPRESS;Initial Catalog=Test;Integrated Security=true");

        public addForm(int selectedCookID,Form1 mainWindow)
        {
            mainForm=mainWindow;
            InitializeComponent();
            receivedCookID = selectedCookID;
        }

        private void helperChefPhone_TextChanged(object sender, EventArgs e)
        {

        }

        private void submitAdd_Click(object sender, EventArgs e)
        {
            string HelperChefIDStr = HelperChefID.Text;
            string helperChefFNStr = helperChefFN.Text;
            string helperChefLNStr = helperChefLN.Text;
            string helperChefExperienceStr = helperChefExperience.Text;
            string helperChefPhoneStr = helperChefPhone.Text;
            string sqlCommand = "INSERT INTO HelperChef (HelperChefID, CookID, FirstName, LastName, Experience,Phone) VALUES (@HelperChefID,@CookID, @FirstName, @LastName, @Experience, @Phone)";


            SqlCommand addHelperChef = new SqlCommand(sqlCommand, connection);
            
            addHelperChef.Parameters.AddWithValue("@HelperChefID", HelperChefIDStr);
            addHelperChef.Parameters.AddWithValue("@CookID", receivedCookID); 
            addHelperChef.Parameters.AddWithValue("@FirstName", helperChefFNStr);
            addHelperChef.Parameters.AddWithValue("@LastName", helperChefLNStr);
            addHelperChef.Parameters.AddWithValue("@Experience", helperChefExperienceStr);
            addHelperChef.Parameters.AddWithValue("@Phone", helperChefPhoneStr);
            
            DataSet ds = new DataSet();
            SqlDataAdapter dataAd = new SqlDataAdapter(addHelperChef);
            try
                {
                
                dataAd.Fill(ds, "HelperChef");
                mainForm.dataGridView2.DataSource = ds.Tables["HelperChef"];
                
                    MessageBox.Show("Record added successfully!");
                    this.Hide();

                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error adding record: " + ex.Message);
                    this.Hide();
                }
                finally
                {
                    connection.Close();
                    this.Hide();
                }
            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
