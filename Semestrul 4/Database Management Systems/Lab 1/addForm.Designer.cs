namespace WindowsFormsApp1Lab1
{
    partial class addForm
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
            this.HelperChefID = new System.Windows.Forms.TextBox();
            this.helperChefFN = new System.Windows.Forms.TextBox();
            this.helperChefLN = new System.Windows.Forms.TextBox();
            this.helperChefExperience = new System.Windows.Forms.TextBox();
            this.helperChefPhone = new System.Windows.Forms.TextBox();
            this.submitAdd = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // HelperChefID
            // 
            this.HelperChefID.Location = new System.Drawing.Point(291, 106);
            this.HelperChefID.Name = "HelperChefID";
            this.HelperChefID.Size = new System.Drawing.Size(191, 20);
            this.HelperChefID.TabIndex = 0;
            // 
            // helperChefFN
            // 
            this.helperChefFN.Location = new System.Drawing.Point(291, 158);
            this.helperChefFN.Name = "helperChefFN";
            this.helperChefFN.Size = new System.Drawing.Size(191, 20);
            this.helperChefFN.TabIndex = 1;
            // 
            // helperChefLN
            // 
            this.helperChefLN.Location = new System.Drawing.Point(291, 211);
            this.helperChefLN.Name = "helperChefLN";
            this.helperChefLN.Size = new System.Drawing.Size(191, 20);
            this.helperChefLN.TabIndex = 2;
            // 
            // helperChefExperience
            // 
            this.helperChefExperience.Location = new System.Drawing.Point(291, 258);
            this.helperChefExperience.Name = "helperChefExperience";
            this.helperChefExperience.Size = new System.Drawing.Size(191, 20);
            this.helperChefExperience.TabIndex = 3;
            // 
            // helperChefPhone
            // 
            this.helperChefPhone.Location = new System.Drawing.Point(291, 307);
            this.helperChefPhone.Name = "helperChefPhone";
            this.helperChefPhone.Size = new System.Drawing.Size(191, 20);
            this.helperChefPhone.TabIndex = 4;
            this.helperChefPhone.TextChanged += new System.EventHandler(this.helperChefPhone_TextChanged);
            // 
            // submitAdd
            // 
            this.submitAdd.Location = new System.Drawing.Point(556, 187);
            this.submitAdd.Name = "submitAdd";
            this.submitAdd.Size = new System.Drawing.Size(138, 67);
            this.submitAdd.TabIndex = 5;
            this.submitAdd.Text = "Add";
            this.submitAdd.UseVisualStyleBackColor = true;
            this.submitAdd.Click += new System.EventHandler(this.submitAdd_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(192, 109);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Helper Chef ID:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(192, 161);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "First Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(192, 214);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Last Name";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(192, 261);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(60, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Experience";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(201, 310);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(38, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Phone";
            // 
            // addForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.submitAdd);
            this.Controls.Add(this.helperChefPhone);
            this.Controls.Add(this.helperChefExperience);
            this.Controls.Add(this.helperChefLN);
            this.Controls.Add(this.helperChefFN);
            this.Controls.Add(this.HelperChefID);
            this.Name = "addForm";
            this.Text = "addForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox HelperChefID;
        private System.Windows.Forms.TextBox helperChefFN;
        private System.Windows.Forms.TextBox helperChefLN;
        private System.Windows.Forms.TextBox helperChefExperience;
        private System.Windows.Forms.TextBox helperChefPhone;
        private System.Windows.Forms.Button submitAdd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}