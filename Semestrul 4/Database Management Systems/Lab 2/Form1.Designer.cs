namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.parentGrid = new System.Windows.Forms.DataGridView();
            this.childGrid = new System.Windows.Forms.DataGridView();
            this.buttonChange = new System.Windows.Forms.Button();
            this.changeToSecondTable = new System.Windows.Forms.Button();
            this.changeToFirstTable = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.parentGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // parentGrid
            // 
            this.parentGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentGrid.Location = new System.Drawing.Point(72, 23);
            this.parentGrid.Name = "parentGrid";
            this.parentGrid.Size = new System.Drawing.Size(548, 200);
            this.parentGrid.TabIndex = 0;
            this.parentGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentGrid_CellContentClick);
            // 
            // childGrid
            // 
            this.childGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childGrid.Location = new System.Drawing.Point(72, 291);
            this.childGrid.Name = "childGrid";
            this.childGrid.Size = new System.Drawing.Size(548, 182);
            this.childGrid.TabIndex = 1;
            this.childGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childGrid_CellContentClick);
            // 
            // buttonChange
            // 
            this.buttonChange.Location = new System.Drawing.Point(783, 314);
            this.buttonChange.Name = "buttonChange";
            this.buttonChange.Size = new System.Drawing.Size(187, 60);
            this.buttonChange.TabIndex = 2;
            this.buttonChange.Text = "Make Changes";
            this.buttonChange.UseVisualStyleBackColor = true;
            this.buttonChange.Click += new System.EventHandler(this.buttonChange_Click);
            // 
            // changeToSecondTable
            // 
            this.changeToSecondTable.Location = new System.Drawing.Point(783, 175);
            this.changeToSecondTable.Name = "changeToSecondTable";
            this.changeToSecondTable.Size = new System.Drawing.Size(187, 48);
            this.changeToSecondTable.TabIndex = 3;
            this.changeToSecondTable.Text = "Change to Second Table";
            this.changeToSecondTable.UseVisualStyleBackColor = true;
            this.changeToSecondTable.Click += new System.EventHandler(this.button1_Click);
            // 
            // changeToFirstTable
            // 
            this.changeToFirstTable.Location = new System.Drawing.Point(783, 102);
            this.changeToFirstTable.Name = "changeToFirstTable";
            this.changeToFirstTable.Size = new System.Drawing.Size(187, 43);
            this.changeToFirstTable.TabIndex = 4;
            this.changeToFirstTable.Text = "Change to First Table";
            this.changeToFirstTable.UseVisualStyleBackColor = true;
            this.changeToFirstTable.Click += new System.EventHandler(this.changeToFirstTable_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1047, 532);
            this.Controls.Add(this.changeToFirstTable);
            this.Controls.Add(this.changeToSecondTable);
            this.Controls.Add(this.buttonChange);
            this.Controls.Add(this.childGrid);
            this.Controls.Add(this.parentGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.parentGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childGrid)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView parentGrid;
        private System.Windows.Forms.DataGridView childGrid;
        private System.Windows.Forms.Button buttonChange;
        private System.Windows.Forms.Button changeToSecondTable;
        private System.Windows.Forms.Button changeToFirstTable;
    }
}

