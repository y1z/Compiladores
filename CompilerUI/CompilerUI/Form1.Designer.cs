namespace CompilerUI
{
   partial class CompilerWindow
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
      this.MainTextBox = new System.Windows.Forms.TextBox();
      this.m_TokenDataView = new System.Windows.Forms.DataGridView();
      this.OutputTextBox = new System.Windows.Forms.TextBox();
      this.dataGridView2 = new System.Windows.Forms.DataGridView();
      this.Name = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.Category = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.Data_Type = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.Length = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.In_Function = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.menuStrip1 = new System.Windows.Forms.MenuStrip();
      this.archivoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.nuevoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.salirToolStripMenuItem = new System.Windows.Forms.ToolStripSeparator();
      this.abrirToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.Guardar = new System.Windows.Forms.ToolStripMenuItem();
      this.gradarComoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.salirToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
      this.compilarToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.compilarToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
      this.guardarTokensToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.guardarTablaDeSimbolosToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.ayudaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.opcionesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.semanticAnalisisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.lexicalAnalisisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.sintacticAnalisisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.Lexim = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.Type = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.Line = new System.Windows.Forms.DataGridViewTextBoxColumn();
      ((System.ComponentModel.ISupportInitialize)(this.m_TokenDataView)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // MainTextBox
      // 
      this.MainTextBox.AcceptsTab = true;
      this.MainTextBox.BackColor = System.Drawing.Color.Indigo;
      this.MainTextBox.Font = new System.Drawing.Font("Lucida Sans", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.MainTextBox.ForeColor = System.Drawing.Color.Yellow;
      this.MainTextBox.Location = new System.Drawing.Point(23, 63);
      this.MainTextBox.Multiline = true;
      this.MainTextBox.Name = "MainTextBox";
      this.MainTextBox.Size = new System.Drawing.Size(1667, 577);
      this.MainTextBox.TabIndex = 0;
      this.MainTextBox.TextChanged += new System.EventHandler(this.MainTextBox_TextChanged);
      // 
      // m_TokenDataView
      // 
      this.m_TokenDataView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.m_TokenDataView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Lexim,
            this.Type,
            this.Line});
      this.m_TokenDataView.GridColor = System.Drawing.SystemColors.Desktop;
      this.m_TokenDataView.Location = new System.Drawing.Point(1691, 63);
      this.m_TokenDataView.Name = "m_TokenDataView";
      this.m_TokenDataView.ReadOnly = true;
      this.m_TokenDataView.RowTemplate.Height = 40;
      this.m_TokenDataView.Size = new System.Drawing.Size(992, 559);
      this.m_TokenDataView.TabIndex = 1;
      this.m_TokenDataView.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
      // 
      // OutputTextBox
      // 
      this.OutputTextBox.BackColor = System.Drawing.SystemColors.ControlText;
      this.OutputTextBox.ForeColor = System.Drawing.SystemColors.HighlightText;
      this.OutputTextBox.Location = new System.Drawing.Point(23, 646);
      this.OutputTextBox.Multiline = true;
      this.OutputTextBox.Name = "OutputTextBox";
      this.OutputTextBox.ReadOnly = true;
      this.OutputTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.OutputTextBox.Size = new System.Drawing.Size(2692, 300);
      this.OutputTextBox.TabIndex = 2;
      this.OutputTextBox.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
      // 
      // dataGridView2
      // 
      this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView2.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Name,
            this.Category,
            this.Data_Type,
            this.Length,
            this.In_Function});
      this.dataGridView2.GridColor = System.Drawing.SystemColors.Desktop;
      this.dataGridView2.Location = new System.Drawing.Point(12, 943);
      this.dataGridView2.Name = "dataGridView2";
      this.dataGridView2.ReadOnly = true;
      this.dataGridView2.RowTemplate.Height = 40;
      this.dataGridView2.Size = new System.Drawing.Size(2617, 236);
      this.dataGridView2.TabIndex = 3;
      this.dataGridView2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
      // 
      // Name
      // 
      this.Name.HeaderText = "Name";
      this.Name.Name = "Name";
      this.Name.ReadOnly = true;
      this.Name.Width = 150;
      // 
      // Category
      // 
      this.Category.HeaderText = "Category";
      this.Category.Name = "Category";
      this.Category.ReadOnly = true;
      this.Category.Width = 150;
      // 
      // Data_Type
      // 
      this.Data_Type.HeaderText = "Data Type";
      this.Data_Type.Name = "Data_Type";
      this.Data_Type.ReadOnly = true;
      this.Data_Type.Width = 150;
      // 
      // Length
      // 
      this.Length.HeaderText = "Length";
      this.Length.Name = "Length";
      this.Length.ReadOnly = true;
      this.Length.Width = 150;
      // 
      // In_Function
      // 
      this.In_Function.HeaderText = "In Function";
      this.In_Function.Name = "In_Function";
      this.In_Function.ReadOnly = true;
      this.In_Function.Width = 200;
      // 
      // menuStrip1
      // 
      this.menuStrip1.ImageScalingSize = new System.Drawing.Size(40, 40);
      this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.archivoToolStripMenuItem,
            this.compilarToolStripMenuItem,
            this.ayudaToolStripMenuItem,
            this.opcionesToolStripMenuItem});
      this.menuStrip1.Location = new System.Drawing.Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new System.Drawing.Size(2695, 49);
      this.menuStrip1.TabIndex = 4;
      this.menuStrip1.Text = "menuStrip1";
      // 
      // archivoToolStripMenuItem
      // 
      this.archivoToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nuevoToolStripMenuItem,
            this.salirToolStripMenuItem,
            this.abrirToolStripMenuItem,
            this.Guardar,
            this.gradarComoToolStripMenuItem,
            this.salirToolStripMenuItem1});
      this.archivoToolStripMenuItem.Name = "archivoToolStripMenuItem";
      this.archivoToolStripMenuItem.Size = new System.Drawing.Size(129, 45);
      this.archivoToolStripMenuItem.Text = "Archivo";
      // 
      // nuevoToolStripMenuItem
      // 
      this.nuevoToolStripMenuItem.Name = "nuevoToolStripMenuItem";
      this.nuevoToolStripMenuItem.Size = new System.Drawing.Size(327, 46);
      this.nuevoToolStripMenuItem.Text = "Nuevo";
      this.nuevoToolStripMenuItem.Click += new System.EventHandler(this.nuevoToolStripMenuItem_Click);
      // 
      // salirToolStripMenuItem
      // 
      this.salirToolStripMenuItem.Name = "salirToolStripMenuItem";
      this.salirToolStripMenuItem.Size = new System.Drawing.Size(324, 6);
      // 
      // abrirToolStripMenuItem
      // 
      this.abrirToolStripMenuItem.Name = "abrirToolStripMenuItem";
      this.abrirToolStripMenuItem.Size = new System.Drawing.Size(327, 46);
      this.abrirToolStripMenuItem.Text = "Abrir";
      this.abrirToolStripMenuItem.Click += new System.EventHandler(this.abrirToolStripMenuItem_Click);
      // 
      // Guardar
      // 
      this.Guardar.Name = "Guardar";
      this.Guardar.Size = new System.Drawing.Size(327, 46);
      this.Guardar.Text = "Guardar";
      this.Guardar.Click += new System.EventHandler(this.gradarToolStripMenuItem_Click);
      // 
      // gradarComoToolStripMenuItem
      // 
      this.gradarComoToolStripMenuItem.Name = "gradarComoToolStripMenuItem";
      this.gradarComoToolStripMenuItem.Size = new System.Drawing.Size(327, 46);
      this.gradarComoToolStripMenuItem.Text = "Guardar Como";
      this.gradarComoToolStripMenuItem.Click += new System.EventHandler(this.gradarComoToolStripMenuItem_Click);
      // 
      // salirToolStripMenuItem1
      // 
      this.salirToolStripMenuItem1.Name = "salirToolStripMenuItem1";
      this.salirToolStripMenuItem1.Size = new System.Drawing.Size(327, 46);
      this.salirToolStripMenuItem1.Text = "Salir";
      this.salirToolStripMenuItem1.Click += new System.EventHandler(this.salirToolStripMenuItem1_Click);
      // 
      // compilarToolStripMenuItem
      // 
      this.compilarToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.compilarToolStripMenuItem1,
            this.guardarTokensToolStripMenuItem,
            this.guardarTablaDeSimbolosToolStripMenuItem});
      this.compilarToolStripMenuItem.Name = "compilarToolStripMenuItem";
      this.compilarToolStripMenuItem.Size = new System.Drawing.Size(150, 45);
      this.compilarToolStripMenuItem.Text = "Compilar";
      // 
      // compilarToolStripMenuItem1
      // 
      this.compilarToolStripMenuItem1.Name = "compilarToolStripMenuItem1";
      this.compilarToolStripMenuItem1.Size = new System.Drawing.Size(492, 46);
      this.compilarToolStripMenuItem1.Text = "Compilar Program";
      this.compilarToolStripMenuItem1.Click += new System.EventHandler(this.compilarToolStripMenuItem1_Click);
      // 
      // guardarTokensToolStripMenuItem
      // 
      this.guardarTokensToolStripMenuItem.Name = "guardarTokensToolStripMenuItem";
      this.guardarTokensToolStripMenuItem.Size = new System.Drawing.Size(492, 46);
      this.guardarTokensToolStripMenuItem.Text = "Guardar Tokens";
      // 
      // guardarTablaDeSimbolosToolStripMenuItem
      // 
      this.guardarTablaDeSimbolosToolStripMenuItem.Name = "guardarTablaDeSimbolosToolStripMenuItem";
      this.guardarTablaDeSimbolosToolStripMenuItem.Size = new System.Drawing.Size(492, 46);
      this.guardarTablaDeSimbolosToolStripMenuItem.Text = "Guardar Tabla de simbolos ";
      // 
      // ayudaToolStripMenuItem
      // 
      this.ayudaToolStripMenuItem.Name = "ayudaToolStripMenuItem";
      this.ayudaToolStripMenuItem.Size = new System.Drawing.Size(113, 45);
      this.ayudaToolStripMenuItem.Text = "Ayuda";
      // 
      // opcionesToolStripMenuItem
      // 
      this.opcionesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.semanticAnalisisToolStripMenuItem,
            this.lexicalAnalisisToolStripMenuItem,
            this.sintacticAnalisisToolStripMenuItem});
      this.opcionesToolStripMenuItem.Name = "opcionesToolStripMenuItem";
      this.opcionesToolStripMenuItem.Size = new System.Drawing.Size(164, 45);
      this.opcionesToolStripMenuItem.Text = "Opciones ";
      // 
      // semanticAnalisisToolStripMenuItem
      // 
      this.semanticAnalisisToolStripMenuItem.Name = "semanticAnalisisToolStripMenuItem";
      this.semanticAnalisisToolStripMenuItem.Size = new System.Drawing.Size(359, 46);
      this.semanticAnalisisToolStripMenuItem.Text = "Semantic Analisis";
      // 
      // lexicalAnalisisToolStripMenuItem
      // 
      this.lexicalAnalisisToolStripMenuItem.Name = "lexicalAnalisisToolStripMenuItem";
      this.lexicalAnalisisToolStripMenuItem.Size = new System.Drawing.Size(359, 46);
      this.lexicalAnalisisToolStripMenuItem.Text = "Lexical Analisis";
      // 
      // sintacticAnalisisToolStripMenuItem
      // 
      this.sintacticAnalisisToolStripMenuItem.Name = "sintacticAnalisisToolStripMenuItem";
      this.sintacticAnalisisToolStripMenuItem.Size = new System.Drawing.Size(359, 46);
      this.sintacticAnalisisToolStripMenuItem.Text = "Sintactic Analisis";
      // 
      // Lexim
      // 
      this.Lexim.Frozen = true;
      this.Lexim.HeaderText = "Lexema";
      this.Lexim.MinimumWidth = 20;
      this.Lexim.Name = "Lexim";
      this.Lexim.ReadOnly = true;
      // 
      // Type
      // 
      this.Type.Frozen = true;
      this.Type.HeaderText = "Type";
      this.Type.MinimumWidth = 20;
      this.Type.Name = "Type";
      this.Type.ReadOnly = true;
      this.Type.Width = 150;
      // 
      // Line
      // 
      this.Line.HeaderText = "Line";
      this.Line.MinimumWidth = 20;
      this.Line.Name = "Line";
      this.Line.ReadOnly = true;
      this.Line.Width = 50;
      // 
      // CompilerWindow
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.AutoSize = true;
      this.ClientSize = new System.Drawing.Size(2695, 1179);
      this.Controls.Add(this.dataGridView2);
      this.Controls.Add(this.OutputTextBox);
      this.Controls.Add(this.m_TokenDataView);
      this.Controls.Add(this.MainTextBox);
      this.Controls.Add(this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      //this.Name = "CompilerWindow";
      this.Text = "Compilador";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.m_TokenDataView)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.TextBox MainTextBox;
      private System.Windows.Forms.DataGridView m_TokenDataView;
      private System.Windows.Forms.TextBox OutputTextBox;
      private System.Windows.Forms.DataGridView dataGridView2;
      private System.Windows.Forms.MenuStrip menuStrip1;
      private System.Windows.Forms.ToolStripMenuItem archivoToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem nuevoToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem Guardar;
      private System.Windows.Forms.ToolStripMenuItem gradarComoToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem compilarToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem compilarToolStripMenuItem1;
      private System.Windows.Forms.ToolStripMenuItem guardarTokensToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem guardarTablaDeSimbolosToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem ayudaToolStripMenuItem;
      private System.Windows.Forms.ToolStripSeparator salirToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem salirToolStripMenuItem1;
      private System.Windows.Forms.ToolStripMenuItem opcionesToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem semanticAnalisisToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem lexicalAnalisisToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem sintacticAnalisisToolStripMenuItem;
      private System.Windows.Forms.DataGridViewTextBoxColumn Name;
      private System.Windows.Forms.DataGridViewTextBoxColumn Category;
      private System.Windows.Forms.DataGridViewTextBoxColumn Data_Type;
      private System.Windows.Forms.DataGridViewTextBoxColumn Length;
      private System.Windows.Forms.DataGridViewTextBoxColumn In_Function;
      private System.Windows.Forms.ToolStripMenuItem abrirToolStripMenuItem;
    private System.Windows.Forms.DataGridViewTextBoxColumn Lexim;
    private System.Windows.Forms.DataGridViewTextBoxColumn Type;
    private System.Windows.Forms.DataGridViewTextBoxColumn Line;
  }
}

