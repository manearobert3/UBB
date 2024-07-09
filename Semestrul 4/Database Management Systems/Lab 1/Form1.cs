using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace WindowsFormsApp1Lab1
{
    public partial class Form1 : Form
    {
         
        int selectedCookID;
        int selectedHelperChefID;
        
        SqlConnection connection = new SqlConnection("Data Source=DESKTOP-6NQQME4\\SQLEXPRESS;Initial Catalog=Test;Integrated Security=true");
         public Form1()
        {
            InitializeComponent();
            dataGridView1.SelectionChanged += dataGridView1_SelectionChanged;
            addButton.Enabled = false;
            deleteButton.Enabled = false;   
            updateButton.Enabled = false;   
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'testDataSet.HelperChef' table. You can move, or remove it, as needed.
            this.helperChefTableAdapter.Fill(this.testDataSet.HelperChef);
            // TODO: This line of code loads data into the 'testDataSet.Cook' table. You can move, or remove it, as needed.
            this.cookTableAdapter.Fill(this.testDataSet.Cook);

        }   

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var id = dataGridView1.Rows[e.RowIndex].Cells[0].Value;
            selectedCookID= (int)dataGridView1.Rows[e.RowIndex].Cells[0].Value;
            addButton.Enabled=true;
            deleteButton.Enabled=false;
            string sqlCommand = "select * from HelperChef where CookID=@CookID";

            SqlCommand getHelperChefByCook = new SqlCommand(sqlCommand, connection);
            getHelperChefByCook.Parameters.AddWithValue("@CookID", id);

            DataSet ds = new DataSet();
            SqlDataAdapter dataAd = new SqlDataAdapter(getHelperChefByCook);

            dataAd.Fill(ds, "HelperChef");
            dataGridView2.DataSource = ds.Tables["HelperChef"];
        }

        

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            selectedHelperChefID = (int)dataGridView2.Rows[e.RowIndex].Cells[0].Value;
            deleteButton.Enabled = true;
            updateButton.Enabled = true;

        }
        private void dataGridView2_SelectionChanged(object sender, DataGridViewCellEventArgs e)
        {
            selectedHelperChefID = (int)dataGridView2.Rows[e.RowIndex].Cells[0].Value;
            deleteButton.Enabled = true;
            updateButton.Enabled = true;
        }
        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            // Enable the button if any row is selected in dataGridView1
            addButton.Enabled = dataGridView1.SelectedRows.Count > 0;
        }
        private void addButton_Click(object sender, EventArgs e)
        {
            addForm addForm = new addForm(selectedCookID,this);
            addForm.Show();
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
           var HelperChefIDStr= dataGridView2.Rows[dataGridView2.CurrentCell.RowIndex].Cells[0].Value;
           var CookIDStr = dataGridView2.Rows[dataGridView2.CurrentCell.RowIndex].Cells[1].Value;
           var helperChefFNStr = dataGridView2.Rows[dataGridView2.CurrentCell.RowIndex].Cells[2].Value;
           var helperChefLNStr = dataGridView2.Rows[dataGridView2.CurrentCell.RowIndex].Cells[3].Value;
           var helperChefExperienceStr = dataGridView2.Rows[dataGridView2.CurrentCell.RowIndex].Cells[4].Value;
           var helperChefPhoneStr = dataGridView2.Rows[dataGridView2.CurrentCell.RowIndex].Cells[5].Value;
            


            string updateCommand = "UPDATE HelperChef SET HelperChefID=@HelperChefID,CookID=@CookID,FirstName=@FirstName,LastName=@LastName,Experience=@Experience,Phone=@Phone WHERE HelperChefID=@CurrHelperChefID";
            SqlCommand cmd = new SqlCommand(updateCommand, connection);

            cmd.Parameters.AddWithValue("@HelperChefID", HelperChefIDStr);
            cmd.Parameters.AddWithValue("@CookID", CookIDStr);
            cmd.Parameters.AddWithValue("@FirstName", helperChefFNStr);
            cmd.Parameters.AddWithValue("@LastName", helperChefLNStr);
            cmd.Parameters.AddWithValue("@Experience", helperChefExperienceStr);
            cmd.Parameters.AddWithValue("@Phone", helperChefPhoneStr);
            cmd.Parameters.AddWithValue("@CurrHelperChefID", selectedHelperChefID);
            DataSet ds = new DataSet();
            SqlDataAdapter dataAd = new SqlDataAdapter(cmd);
            try
            {
                dataAd.Fill(ds, "HelperChef");
                dataGridView2.DataSource = ds.Tables["HelperChef"];

         
                MessageBox.Show("Changes saved successfully.");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error saving changes: " + ex.Message);
            }
           
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            string deleteCommand = "DELETE FROM HelperChef WHERE HelperChefID = @HelperChefID";

         
            SqlCommand cmd = new SqlCommand(deleteCommand, connection);
            
                
            cmd.Parameters.AddWithValue("@HelperChefID", selectedHelperChefID);
            DataSet ds = new DataSet();
            SqlDataAdapter dataAd = new SqlDataAdapter(cmd);
            try
                {
                
                dataAd.Fill(ds, "HelperChef");
                dataGridView2.DataSource = ds.Tables["HelperChef"];
                MessageBox.Show("Entry deleted successfully.");
            }
                catch (Exception ex)
                {
                    MessageBox.Show("Error deleting entry: " + ex.Message);
                }
                finally
                {
                    deleteButton.Enabled = false;

                }
            
        }
    }
}
