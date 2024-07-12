Imports System.Data.OleDb
Public Class Borrower_Profile
    Public Property Hey As String = SignINUser.TextBox1.Text
    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Me.Hide()
        User_Data.Show()

    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        Me.Close()
        SignINUser.Show()
    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
  
        Me.Hide()
        Borrow__Return_Form.Show()
    End Sub

    Private Sub Borrower_Profile_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        'TODO: This line of code loads data into the 'BookActionsDataSet.Books_And_User' table. You can move, or remove it, as needed.
        Me.Books_And_UserTableAdapter.Fill(Me.BookActionsDataSet.Books_And_User)

        Label1.Text = "Welcome " & Hey & "!"
    End Sub

    Private Sub Label1_Click(sender As System.Object, e As System.EventArgs) Handles Label1.Click

    End Sub
End Class