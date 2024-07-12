Imports System.Data.OleDb
Imports System.Data
Public Class SignUp

    Private Property insert As Object

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Dim iexit As DialogResult
        iexit = MessageBox.Show("Are you sure you want to exit?", "CLose", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If iexit = DialogResult.Yes Then
            TextBox1.Text = ""
            TextBox2.Text = ""
            TextBox3.Text = ""
            TextBox4.Text = ""
            TextBox5.Text = ""
            TextBox6.Text = ""
            TextBox7.Text = ""
            Me.Close()
            SignINUser.Show()
        End If
    End Sub

    Private Sub TextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox1.TextChanged
        If TextBox1.Text.Length >= 1 Then
            Label16.Visible = False
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

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
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

        Dim iexit As DialogResult
        If Label7.Visible = False And Label19.Visible = False And Label18.Visible = False And Label17.Visible = False And Label28.Visible = False And Label16.Visible = False And Label9.Visible = False And Label11.Visible = False Then
            On Error GoTo SaveErr
            UsersBindingSource.EndEdit()
            UsersTableAdapter.Update(Database1DataSet.Users)
            MessageBox.Show("Account Successfully Created!")
            TextBox1.Text = ""
            TextBox2.Text = ""
            TextBox3.Text = ""
            TextBox4.Text = ""
            TextBox5.Text = ""
            TextBox6.Text = ""
            TextBox7.Text = ""
            iexit = MessageBox.Show("Do you wish to continue to Menu?", "Continue or Stay?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)




SaveErr:
        End If


        If Label7.Visible = False And Label19.Visible = False And Label18.Visible = False And Label17.Visible = False And Label28.Visible = False And Label16.Visible = False And Label9.Visible = False And Label11.Visible = False Then


        End If
        If iexit = DialogResult.Yes Then
            Me.Close()
            Loading.Show()
        End If

    End Sub

    Private Sub Label28_Click(sender As System.Object, e As System.EventArgs) Handles Label28.Click

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

    Private Sub TextBox4_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox4.TextChanged
        If TextBox4.Text.Length >= 1 Then
            Label19.Visible = False
        End If
    End Sub

    Private Sub TextBox5_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox5.TextChanged
        If TextBox5.Text.Length >= 1 Then
            Label19.Visible = False
        End If
    End Sub

    Private Sub Form3_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        'TODO: This line of code loads data into the 'Database1DataSet.Users' table. You can move, or remove it, as needed.
        Me.UsersTableAdapter.Fill(Me.Database1DataSet.Users)
        TextBox5.UseSystemPasswordChar = False
        Dim ans As DialogResult
        ans = MessageBox.Show("Welcome to Sign Up Form!", "Message", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        If ans = DialogResult.OK Then

            UsersBindingSource.AddNew()

        End If
        TextBox1.Text = ""
        TextBox2.Text = ""
        TextBox3.Text = ""
        TextBox4.Text = ""
        TextBox5.Text = ""
        TextBox6.Text = ""
        TextBox7.Text = ""


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

    Private Sub Label11_Click(sender As System.Object, e As System.EventArgs) Handles Label11.Click

    End Sub

    Private Sub Label1_Click(sender As System.Object, e As System.EventArgs) Handles Label1.Click

    End Sub

    Private Sub Label2_Click(sender As System.Object, e As System.EventArgs) Handles Label2.Click

    End Sub

    Private Sub Label3_Click(sender As System.Object, e As System.EventArgs) Handles Label3.Click

    End Sub

    Private Sub Label4_Click(sender As System.Object, e As System.EventArgs) Handles Label4.Click

    End Sub

    Private Sub Label16_Click(sender As System.Object, e As System.EventArgs) Handles Label16.Click

    End Sub

    Private Sub Label17_Click(sender As System.Object, e As System.EventArgs) Handles Label17.Click

    End Sub

    Private Sub Label18_Click(sender As System.Object, e As System.EventArgs) Handles Label18.Click

    End Sub

    Private Sub Label19_Click(sender As System.Object, e As System.EventArgs) Handles Label19.Click

    End Sub

    Private Sub Label26_Click(sender As System.Object, e As System.EventArgs) Handles Label26.Click

    End Sub

    Private Sub Label5_Click(sender As System.Object, e As System.EventArgs) Handles Label5.Click

    End Sub

    Private Sub Label7_Click(sender As System.Object, e As System.EventArgs) Handles Label7.Click

    End Sub

    Private Sub Label8_Click(sender As System.Object, e As System.EventArgs) Handles Label8.Click

    End Sub

    Private Sub Label9_Click(sender As System.Object, e As System.EventArgs) Handles Label9.Click

    End Sub

    Private Sub Label10_Click(sender As System.Object, e As System.EventArgs) Handles Label10.Click

    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        If TextBox5.UseSystemPasswordChar = False Then
            TextBox5.UseSystemPasswordChar = True
        Else
            TextBox5.UseSystemPasswordChar = False
        End If
    End Sub

End Class