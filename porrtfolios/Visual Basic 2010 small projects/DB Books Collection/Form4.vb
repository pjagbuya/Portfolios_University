Public Class Form4

    Private Sub TextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox1.TextChanged

    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        If TextBox1.Text = My.Settings.Password Then
            MessageBox.Show("Success")
            Librarian.Show()
            TextBox1.Text = ""
            Me.Hide()
        Else
            MessageBox.Show("Error")
        End If
    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        TextBox1.Text = ""
        Me.Close()

        Loading.Show()
    End Sub

    Private Sub Form4_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        TextBox1.Text = ""
    End Sub
End Class