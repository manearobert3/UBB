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
using System.Configuration;
using System.Collections.Specialized;
namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private string parentTable =ConfigurationManager.AppSettings.Get("parentTable");
        private string childTable = ConfigurationManager.AppSettings.Get("childTable");
        private string foreignKeyConstraint = ConfigurationManager.AppSettings.Get("foreignKeyConstraint");
        private DataSet dataSet = new DataSet();
        private string primaryKey = ConfigurationManager.AppSettings.Get("primaryKey");
        private string foreignKey = ConfigurationManager.AppSettings.Get("foreignKey");
        private string selectAllFromParent = ConfigurationManager.AppSettings.Get("selectAllFromParent");
        private string selectAllFromChild = ConfigurationManager.AppSettings.Get("selectAllFromChild");
        private SqlDataAdapter parentDataAdapter, childDataAdapter;
        private BindingSource bindingSourceParentTable = new BindingSource();
        private BindingSource bindingSourceChildTable = new BindingSource();

        SqlConnection connection = new SqlConnection("Data Source=DESKTOP-6NQQME4\\SQLEXPRESS;Initial Catalog=Test;Integrated Security=true");

        public Form1()
        {
            InitializeComponent();
            parentDataAdapter = new SqlDataAdapter(selectAllFromParent,connection);
            childDataAdapter= new SqlDataAdapter(selectAllFromChild, connection);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            parentDataAdapter.Fill(dataSet, parentTable);
            childDataAdapter.Fill(dataSet, childTable);
            DataRelation dataRelation = new DataRelation(
                foreignKeyConstraint,
                dataSet.Tables[parentTable].Columns[primaryKey],
                dataSet.Tables[childTable].Columns[foreignKey]);
            dataSet.Relations.Add(dataRelation);
            bindingSourceParentTable.DataSource = dataSet;
            bindingSourceParentTable.DataMember = parentTable;
            bindingSourceChildTable.DataSource = bindingSourceParentTable;
            bindingSourceChildTable.DataMember = foreignKeyConstraint;

            parentGrid.DataSource = bindingSourceParentTable;
            childGrid.DataSource = bindingSourceChildTable;
        }

        private void childGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void parentGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            dataSet.Tables[childTable].Clear();
            var id = parentGrid.Rows[e.RowIndex].Cells[primaryKey].Value;
            string sqlCommand = selectAllFromChild + " WHERE " + childTable + "." + foreignKey + " = @id";
            SqlCommand getChildByParent = new SqlCommand(sqlCommand, connection);
            getChildByParent.Parameters.AddWithValue("@id", id);
            SqlDataAdapter dataAd = new SqlDataAdapter(getChildByParent);

            dataAd.Fill(dataSet, childTable);
            childGrid.DataSource = dataSet.Tables[childTable];
        }

        private void button1_Click(object sender, EventArgs e)
        {
            parentTable = ConfigurationManager.AppSettings.Get("parentTable");
            childTable = ConfigurationManager.AppSettings.Get("childTable");
            foreignKeyConstraint = ConfigurationManager.AppSettings.Get("foreignKeyConstraint");
            dataSet = new DataSet();
            primaryKey = ConfigurationManager.AppSettings.Get("primaryKey");
            foreignKey = ConfigurationManager.AppSettings.Get("foreignKey");
            selectAllFromParent = ConfigurationManager.AppSettings.Get("selectAllFromParent");
            selectAllFromChild = ConfigurationManager.AppSettings.Get("selectAllFromChild");

            bindingSourceParentTable = new BindingSource();
            bindingSourceChildTable = new BindingSource();
            parentDataAdapter = new SqlDataAdapter(selectAllFromParent, connection);
            childDataAdapter = new SqlDataAdapter(selectAllFromChild, connection);
            Form1_Load(sender, e);
        }

        private void changeToFirstTable_Click(object sender, EventArgs e)
        {
            parentTable = ConfigurationManager.AppSettings.Get("parentTable1");
            childTable = ConfigurationManager.AppSettings.Get("childTable1");
            foreignKeyConstraint = ConfigurationManager.AppSettings.Get("foreignKeyConstraint1");
            dataSet = new DataSet();
            primaryKey = ConfigurationManager.AppSettings.Get("primaryKey1");
            foreignKey = ConfigurationManager.AppSettings.Get("foreignKey1");
            selectAllFromParent = ConfigurationManager.AppSettings.Get("selectAllFromParent1");
            selectAllFromChild = ConfigurationManager.AppSettings.Get("selectAllFromChild1");

            bindingSourceParentTable = new BindingSource();
            bindingSourceChildTable = new BindingSource();
            parentDataAdapter = new SqlDataAdapter(selectAllFromParent, connection);
            childDataAdapter = new SqlDataAdapter(selectAllFromChild, connection);
            Form1_Load(sender, e);
        }

        private void buttonChange_Click(object sender, EventArgs e)
        {
            try
            {
                SqlCommandBuilder sqlCommandBuilder = new SqlCommandBuilder(childDataAdapter);
                sqlCommandBuilder.GetInsertCommand();
                parentDataAdapter.Update(dataSet, parentTable);

                childDataAdapter.Update(dataSet, childTable);
                childGrid.DataSource = dataSet.Tables[childTable];
            }
            catch (Exception ex)
            {
                
                MessageBox.Show($"An error occurred: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        
    }
}
