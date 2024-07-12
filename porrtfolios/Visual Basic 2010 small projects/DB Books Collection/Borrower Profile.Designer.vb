<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Borrower_Profile
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.DataGridView1 = New System.Windows.Forms.DataGridView()
        Me.AccountNumberDataGridViewTextBoxColumn = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.UsernameDataGridViewTextBoxColumn = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.BookDataGridViewTextBoxColumn = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.BooksAndUserBindingSource = New System.Windows.Forms.BindingSource(Me.components)
        Me.BookActionsDataSet = New ICT_2nd_Project.BookActionsDataSet()
        Me.Books_And_UserTableAdapter = New ICT_2nd_Project.BookActionsDataSetTableAdapters.Books_And_UserTableAdapter()
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BooksAndUserBindingSource, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BookActionsDataSet, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(50, 64)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(244, 188)
        Me.Button1.TabIndex = 0
        Me.Button1.Text = "View/Modify User Data"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(313, 64)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(244, 188)
        Me.Button2.TabIndex = 1
        Me.Button2.Text = "Borrow/Return Books"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(238, 275)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(129, 31)
        Me.Button3.TabIndex = 2
        Me.Button3.Text = "Exit"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Label1.Location = New System.Drawing.Point(271, 28)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(52, 13)
        Me.Label1.TabIndex = 3
        Me.Label1.Text = "Welcome"
        '
        'DataGridView1
        '
        Me.DataGridView1.AutoGenerateColumns = False
        Me.DataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.DataGridView1.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.AccountNumberDataGridViewTextBoxColumn, Me.UsernameDataGridViewTextBoxColumn, Me.BookDataGridViewTextBoxColumn})
        Me.DataGridView1.DataSource = Me.BooksAndUserBindingSource
        Me.DataGridView1.Location = New System.Drawing.Point(80, 275)
        Me.DataGridView1.Name = "DataGridView1"
        Me.DataGridView1.Size = New System.Drawing.Size(93, 44)
        Me.DataGridView1.TabIndex = 4
        Me.DataGridView1.Visible = False
        '
        'AccountNumberDataGridViewTextBoxColumn
        '
        Me.AccountNumberDataGridViewTextBoxColumn.DataPropertyName = "Account Number"
        Me.AccountNumberDataGridViewTextBoxColumn.HeaderText = "Account Number"
        Me.AccountNumberDataGridViewTextBoxColumn.Name = "AccountNumberDataGridViewTextBoxColumn"
        '
        'UsernameDataGridViewTextBoxColumn
        '
        Me.UsernameDataGridViewTextBoxColumn.DataPropertyName = "Username"
        Me.UsernameDataGridViewTextBoxColumn.HeaderText = "Username"
        Me.UsernameDataGridViewTextBoxColumn.Name = "UsernameDataGridViewTextBoxColumn"
        '
        'BookDataGridViewTextBoxColumn
        '
        Me.BookDataGridViewTextBoxColumn.DataPropertyName = "Book"
        Me.BookDataGridViewTextBoxColumn.HeaderText = "Book"
        Me.BookDataGridViewTextBoxColumn.Name = "BookDataGridViewTextBoxColumn"
        '
        'BooksAndUserBindingSource
        '
        Me.BooksAndUserBindingSource.DataMember = "Books And User"
        Me.BooksAndUserBindingSource.DataSource = Me.BookActionsDataSet
        '
        'BookActionsDataSet
        '
        Me.BookActionsDataSet.DataSetName = "BookActionsDataSet"
        Me.BookActionsDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema
        '
        'Books_And_UserTableAdapter
        '
        Me.Books_And_UserTableAdapter.ClearBeforeFill = True
        '
        'Borrower_Profile
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(647, 360)
        Me.Controls.Add(Me.DataGridView1)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Name = "Borrower_Profile"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Borrower_Profile"
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BooksAndUserBindingSource, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BookActionsDataSet, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents DataGridView1 As System.Windows.Forms.DataGridView
    Friend WithEvents BookActionsDataSet As ICT_2nd_Project.BookActionsDataSet
    Friend WithEvents BooksAndUserBindingSource As System.Windows.Forms.BindingSource
    Friend WithEvents Books_And_UserTableAdapter As ICT_2nd_Project.BookActionsDataSetTableAdapters.Books_And_UserTableAdapter
    Friend WithEvents AccountNumberDataGridViewTextBoxColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents UsernameDataGridViewTextBoxColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents BookDataGridViewTextBoxColumn As System.Windows.Forms.DataGridViewTextBoxColumn
End Class
