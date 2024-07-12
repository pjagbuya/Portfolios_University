Public Class Librarian

    Private Sub Librarian_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        'TODO: This line of code loads data into the 'Database1DataSet.Users' table. You can move, or remove it, as needed.
        Me.UsersTableAdapter.Fill(Me.Database1DataSet.Users)

    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Dim iexit As DialogResult
        iexit = MessageBox.Show("Are you sure you want to exit this form", "Close", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If iexit = DialogResult.Yes Then
            MessageBox.Show("Thank You!")
            Me.Close()
            Loading.Show()
        End If
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Me.Hide()
        Book_Collections.Show()

    End Sub

    Private Sub Button9_Click(sender As System.Object, e As System.EventArgs) Handles Button9.Click
        If TextBox1.Enabled = False And TextBox2.Enabled = False And TextBox3.Enabled = False And TextBox4.Enabled = False And TextBox5.Enabled = False And TextBox6.Enabled = False And TextBox7.Enabled = False Then
            TextBox1.Enabled = True
            TextBox2.Enabled = True
            TextBox3.Enabled = True
            TextBox4.Enabled = True
            TextBox5.Enabled = True
            TextBox6.Enabled = True
            TextBox7.Enabled = True
        Else
            TextBox1.Enabled = False
            TextBox2.Enabled = False
            TextBox3.Enabled = False
            TextBox4.Enabled = False
            TextBox5.Enabled = False
            TextBox6.Enabled = False
            TextBox7.Enabled = False
        End If
    End Sub

    Private Sub Button5_Click(sender As System.Object, e As System.EventArgs) Handles Button5.Click
        If TextBox7.Text = "" Then
            Label11.Visible = True
        End If
        If TextBox6.Text = "" Then
            Label9.Visible = True
        End If

        If TextBox1.Text.Length = vbEmpty Then

            Label16.Visible = True
        Else
            Label16.Visible = False
        End If
        If TextBox2.Text.Length <= 10 Then
            TextBox2.Text = ""
            Label28.Visible = True
            Label17.Visible = True
        Else
            Label28.Visible = False
            Label17.Visible = False
        End If
        If TextBox3.Text = "" Then
            Label18.Visible = True
        End If
        If TextBox4.Text = "" Then
            Label19.Visible = True
        End If
        If TextBox5.Text = "" Then
            Label7.Visible = True
        End If
        If Label7.Visible = False And Label19.Visible = False And Label18.Visible = False And Label17.Visible = False And Label28.Visible = False And Label16.Visible = False And Label9.Visible = False And Label11.Visible = False Then
            On Error GoTo SaveErr
            UsersBindingSource.EndEdit()
            UsersTableAdapter.Update(Database1DataSet.Users)
SaveErr:
        End If

    End Sub

    Private Sub TextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox1.TextChanged
        If TextBox1.Text.Length >= 1 Then
            Label16.Visible = False
        End If
    End Sub

    Private Sub TextBox6_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox6.TextChanged
        If TextBox6.Text.Length >= 1 Then
            Label9.Visible = False
        End If
    End Sub

    Private Sub TextBox7_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox7.TextChanged
        If TextBox7.Text.Length >= 1 Then
            Label11.Visible = False
        End If
    End Sub

    Private Sub TextBox2_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox2.TextChanged
        If TextBox2.Text.Length >= 1 Then
            Label26.Visible = False
            Label28.Visible = False
            Label17.Visible = False
        Else
            Label26.Visible = True
        End If
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
            Label18.Visible = False
        End If
    End Sub

    Private Sub TextBox4_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox4.TextChanged
        If TextBox4.Text.Length >= 1 Then
            Label19.Visible = False
        End If
    End Sub

    Private Sub TextBox5_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox5.TextChanged
        If TextBox4.Text.Length >= 1 Then
            Label19.Visible = False
        End If
    End Sub

    Private Sub Button8_Click(sender As System.Object, e As System.EventArgs) Handles Button8.Click
        If TextBox5.UseSystemPasswordChar = False Then
            TextBox5.UseSystemPasswordChar = True
        Else
            TextBox5.UseSystemPasswordChar = False
        End If
    End Sub

    Private Sub Button7_Click(sender As System.Object, e As System.EventArgs) Handles Button7.Click
        UsersBindingSource.MoveNext()

    End Sub

    Private Sub Button6_Click(sender As System.Object, e As System.EventArgs) Handles Button6.Click
        UsersBindingSource.MovePrevious()

    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        UsersBindingSource.AddNew()

    End Sub

    Private Sub Button4_Click(sender As System.Object, e As System.EventArgs) Handles Button4.Click
        Dim sure As DialogResult
        sure = MessageBox.Show("Are you sure you want to remove this user?", "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
        If sure = DialogResult.Yes Then
            UsersBindingSource.RemoveCurrent()
        End If
    End Sub
End Class