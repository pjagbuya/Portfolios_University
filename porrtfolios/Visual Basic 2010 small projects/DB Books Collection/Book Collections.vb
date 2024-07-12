Imports System.Data.OleDb
Public Class Book_Collections
    Public Property Book As String
    Private Sub Book_Collections_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        'TODO: This line of code loads data into the 'BookActionsDataSet.Books_And_User' table. You can move, or remove it, as needed.
        Me.Books_And_UserTableAdapter.Fill(Me.BookActionsDataSet.Books_And_User)


        'TODO: This line of code loads data into the 'Better_BOoksDataSet.Table1' table. You can move, or remove it, as needed.
        Me.Table1TableAdapter.Fill(Me.Better_BOoksDataSet.Table1)
        'TODO: This line of code loads data into the 'BOOKSDataSet.Paste_Errors' table. You can move, or remove it, as needed.

        'TODO: This line of code loads data into the 'BOOKSDataSet.Table1' table. You can move, or remove it, as needed.
        

    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        Table1BindingSource3.AddNew()

    End Sub

    Private Sub Button6_Click(sender As System.Object, e As System.EventArgs) Handles Button6.Click
        Dim iexit As DialogResult
        iexit = MessageBox.Show("Are you sure you want to exit this form", "Close", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If iexit = DialogResult.Yes Then
            MessageBox.Show("Thank You!")
            Me.Close()
            Librarian.Show()
        End If
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Table1BindingSource3.MoveNext()

    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Table1BindingSource3.MovePrevious()

    End Sub

    Private Sub Button4_Click(sender As System.Object, e As System.EventArgs) Handles Button4.Click
        Dim sure As DialogResult
        sure = MessageBox.Show("Are you sure you want to remove this Book?", "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
        If sure = DialogResult.Yes Then
            Table1BindingSource3.RemoveCurrent()
        End If
    End Sub

    Private Sub Button5_Click(sender As System.Object, e As System.EventArgs) Handles Button5.Click
        On Error GoTo SaveErr
        Table1BindingSource3.EndEdit()
      
        Table1TableAdapter.Update(Better_BOoksDataSet.Table1)
SaveErr:



    End Sub

    Private Sub Label11_Click(sender As System.Object, e As System.EventArgs) Handles Label11.Click

    End Sub




    Private Sub TextBox12_KeyPress(sender As Object, e As System.Windows.Forms.KeyPressEventArgs) Handles TextBox12.KeyPress
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

    Private Sub TextBox12_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox12.TextChanged

    End Sub

    Private Sub TextBox9_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox9.TextChanged
        Dim search As String = "%" + TextBox9.Text + "%"
        Me.Table1TableAdapter.FillByBook(Me.Better_BOoksDataSet.Table1, search, search)
    End Sub

    Private Sub Button7_Click(sender As System.Object, e As System.EventArgs)

    End Sub

    Private Sub Button7_Click_1(sender As System.Object, e As System.EventArgs) Handles Button7.Click
        Me.Table1TableAdapter.Fill(Me.Better_BOoksDataSet.Table1)
    End Sub

    Private Sub Button8_Click(sender As System.Object, e As System.EventArgs) Handles Button8.Click

    End Sub
End Class