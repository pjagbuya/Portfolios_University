Imports System.Data.OleDb
Imports ICT_2nd_Project.Database1DataSetTableAdapters

Public Class User_Data
    Private Sub Table1BindingNavigatorSaveItem_Click(sender As System.Object, e As System.EventArgs)

    End Sub
    Private Sub TextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox1.TextChanged
        If TextBox1.Text.Length >= 1 Then
            Label16.Visible = False
        End If
    End Sub
    Private Sub Label8_Click(sender As System.Object, e As System.EventArgs) Handles Label8.Click

    End Sub
    Private Sub TextBox6_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox6.TextChanged
        If TextBox6.Text.Length >= 1 Then
            Label9.Visible = False
        End If
    End Sub
    Private Sub Label1_Click(sender As System.Object, e As System.EventArgs) Handles Label1.Click

    End Sub
    Private Sub User_Data_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        'TODO: This line of code loads data into the 'Database1DataSet.Users' table. You can move, or remove it, as needed.

        'Me.UsersTableAdapter.Fill(Me.Database1DataSet.Users)

        TextBox5.UseSystemPasswordChar = False
        TextBox4.Text = SignINUser.TextBox1.Text
        Dim Search3 As String = TextBox4.Text
        Me.UsersTableAdapter.FillBySearchMe(Me.Database1DataSet.Users, Search3, Search3)
    End Sub

    Private Sub TextBox7_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox7.TextChanged
        If TextBox6.Text.Length >= 1 Then
            Label9.Visible = False
        End If
    End Sub

    Private Sub Label10_Click(sender As System.Object, e As System.EventArgs) Handles Label10.Click

    End Sub

    Private Sub Label16_Click(sender As System.Object, e As System.EventArgs) Handles Label16.Click

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
        iexit = MessageBox.Show("Are you sure about these changes", "Question", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If iexit = Windows.Forms.DialogResult.Yes Then


            If Label7.Visible = False And Label19.Visible = False And Label18.Visible = False And Label17.Visible = False And Label28.Visible = False And Label16.Visible = False And Label9.Visible = False And Label11.Visible = False Then
                On Error GoTo SaveErr
                UsersBindingSource.EndEdit()
                UsersTableAdapter.Update(Database1DataSet.Users)
                MessageBox.Show("Successfully Saved")
            ElseIf Label7.Visible = True Or Label19.Visible = True Or Label18.Visible = True Or Label17.Visible = True Or Label28.Visible = True Or Label16.Visible = False Or Label9.Visible = True Or Label11.Visible = True Then
                MessageBox.Show("Error")
SaveErr:
            End If
        End If
    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Me.Close()
        Borrower_Profile.Show()

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
        If TextBox5.Text.Length >= 1 Then
            Label7.Visible = False
        End If
    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        If TextBox5.UseSystemPasswordChar = False Then
            TextBox5.UseSystemPasswordChar = True
        Else
            TextBox5.UseSystemPasswordChar = False
        End If
    End Sub


End Class