Imports System.Data.OleDb
Public Class Borrow__Return_Form
    Public Property Lbl As String = SignINUser.TextBox1.Text
    Public Property Book As String
    Public Property Hey As String = SignINUser.TextBox1.Text
    



    Private Sub Borrow__Return_Form_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        TextBox1.Text = ""
        TextBox2.Text = ""
        TextBox3.Text = ""
        'TODO: This line of code loads data into the 'BookActionsDataSet.Books_And_User' table. You can move, or remove it, as needed.
        Me.Books_And_UserTableAdapter.Fill(Me.BookActionsDataSet.Books_And_User)
        'TODO: This line of code loads data into the 'Database1DataSet.Users' table. You can move, or remove it, as needed.
        Me.UsersTableAdapter.Fill(Me.Database1DataSet.Users)
        'TODO: This line of code loads data into the 'Better_BOoksDataSet.Table1' table. You can move, or remove it, as needed.
        'Me.Table1TableAdapter.Fill(Me.Better_BOoksDataSet.Table1)
        Label28.Text = Lbl
     
        Dim search2 As String = Label28.Text
        Me.UsersTableAdapter.FillBySearchThing(Me.Database1DataSet.Users, search2, search2)
        Dim response2 As DialogResult
        Dim response As DialogResult
        response = MessageBox.Show("Do you wish to Borrow books?", "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
        If response = DialogResult.Yes Then
            BooksAndUserBindingSource.AddNew()
        End If
        If response = DialogResult.No Then
            BooksAndUserBindingSource.AddNew()
            response2 = MessageBox.Show("Then You Are Returning Book/s", "Message", MessageBoxButtons.OK, MessageBoxIcon.Information)
            TextBox4.Enabled = False
            TextBox3.Enabled = False
        End If
        TextBox1.Text = ""
        TextBox2.Text = ""
        TextBox3.Text = ""
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
    
    End Sub



    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        Dim iexit As DialogResult
        iexit = MessageBox.Show("Are you sure you want to exit this form?", "CLose", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If iexit = DialogResult.Yes Then
            MessageBox.Show("Thank You!")
            Me.Close()
            Borrower_Profile.Show()
        End If
    End Sub

    Private Sub Label16_Click(sender As System.Object, e As System.EventArgs) Handles Label16.Click

    End Sub

    Private Sub Label15_Click(sender As System.Object, e As System.EventArgs) Handles Label15.Click

    End Sub

    Private Sub Label14_Click(sender As System.Object, e As System.EventArgs) Handles Label14.Click

    End Sub

    Private Sub Label13_Click(sender As System.Object, e As System.EventArgs) Handles Label13.Click

    End Sub

    Private Sub Button4_Click(sender As System.Object, e As System.EventArgs) Handles Button4.Click
        If TextBox4.Text = "" Then
            Label25.Visible = True
        Else
            Label25.Visible = False
        End If
        If TextBox2.Text = "" Then
            Label25.Visible = True
        Else
            Label25.Visible = False
        End If
        If TextBox3.Text = "" Then
            Label25.Visible = True
        Else
            Label25.Visible = False
        End If
        If TextBox4.Text = Hey Then
            If Label25.Visible = False Then

                MessageBox.Show("Successfully Borrowed!")
                On Error GoTo SaveErr
                BooksAndUserBindingSource.EndEdit()
                Books_And_UserTableAdapter.Update(BookActionsDataSet.Books_And_User)

SaveErr:
            Else

                MessageBox.Show("Error")
            End If
        Else
            MessageBox.Show("User Not Found", "Error")
        End If
    End Sub

    Private Sub Button5_Click(sender As System.Object, e As System.EventArgs) Handles Button5.Click
        If TextBox2.Text = "" Then
            Label25.Visible = True
        Else
            Label25.Visible = False
        End If
       
        
        If Label25.Visible = False Then
    
                MessageBox.Show("Successfully Returned!")

                BooksAndUserBindingSource1.RemoveCurrent()
                BooksAndUserBindingSource1.EndEdit()
                Books_And_UserTableAdapter.Update(BookActionsDataSet.Books_And_User)

SaveErr:
            End If

    End Sub

    Private Sub Button6_Click(sender As System.Object, e As System.EventArgs) Handles Button6.Click
        MessageBox.Show("Your Account Number is no. " & Label26.Text)
    End Sub

    Private Sub Button7_Click(sender As System.Object, e As System.EventArgs) Handles Button7.Click
            Me.Table1TableAdapter.Fill(Me.Better_BOoksDataSet.Table1)

    End Sub

    Private Sub Button9_Click(sender As System.Object, e As System.EventArgs) Handles Button9.Click
        Table1BindingSource1.MoveNext()
    End Sub

    Private Sub Button8_Click(sender As System.Object, e As System.EventArgs) Handles Button8.Click
        Table1BindingSource1.MovePrevious()
    End Sub

    Private Sub TextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox1.TextChanged
        Dim search As String = "%" + TextBox1.Text + "%"
        Me.Table1TableAdapter.FillBySearchThis(Me.Better_BOoksDataSet.Table1, search, search)
    End Sub

    Private Sub TextBox3_KeyPress(sender As Object, e As System.Windows.Forms.KeyPressEventArgs) Handles TextBox3.KeyPress
        If (e.KeyChar < "0" OrElse e.KeyChar > "9") _
AndAlso e.KeyChar <> ControlChars.Back AndAlso e.KeyChar <> "." AndAlso e.KeyChar <> "," Then
            e.Handled = True
        End If
        If Asc(e.KeyChar) = 8 Then
            e.Handled = False
        ElseIf Asc(e.KeyChar) = 32 Then
            e.Handled = False
        ElseIf Asc(e.KeyChar) = 46 Then
            e.Handled = False
        End If
    End Sub

    Private Sub TextBox3_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox3.TextChanged
        If TextBox3.Text.Length >= 1 Then
            Label25.Visible = False
        End If
    End Sub

   
   

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Me.Hide()
        Users_Book_Collection.Show()
    End Sub


    Private Sub TextBox2_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox2.TextChanged
        If TextBox2.Text.Length >= 1 Then
            Label25.Visible = False
        End If
        Dim response2 As DialogResult
        If response2 = DialogResult.OK Then
            Dim search4 As String = "%" + TextBox2.Text + "%"
            Books_And_UserTableAdapter.FillByReturn(BookActionsDataSet.Books_And_User, search4, search4)
        End If
    End Sub

    Private Sub TextBox4_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox4.TextChanged
        If TextBox3.Text.Length >= 1 Then
            Label25.Visible = False
        End If
    End Sub

    Private Sub Button10_Click(sender As System.Object, e As System.EventArgs) Handles Button10.Click
        MessageBox.Show("Your username is " & Hey)
    End Sub
End Class