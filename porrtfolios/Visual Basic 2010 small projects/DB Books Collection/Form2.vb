Imports System.Data.OleDb
Imports System
Imports ICT_2nd_Project.Database1DataSet.UsersDataTable
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Linq
Imports System.Text
Imports System.Windows.Forms
Imports System.Threading.Tasks
Imports System.Data.DataColumn
Public Class SignINUser

    Private Sub Form2_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load

        TextBox1.Text = ""
        TextBox2.Text = ""



    End Sub

    Private Sub LinkLabel1_LinkClicked(sender As System.Object, e As System.Windows.Forms.LinkLabelLinkClickedEventArgs) Handles LinkLabel1.LinkClicked
        Me.Close()
        SignUp.Show()
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click

        Dim username As String = ""
        Dim password As String
        Dim user As String = ""
        Dim pass As String
        If TextBox1.Text = "" Or TextBox2.Text = "" Then
            MessageBox.Show("Please completely fill the required datas", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
        Else
            username = TextBox1.Text
            password = TextBox2.Text


            Dim que As String = "Select password From Users where username= '" & username & "';"
            Dim source As String = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=|DataDirectory|\Database1.mdb"
            Dim con = New OleDbConnection(source)
            Dim cmd As New OleDbCommand(que, con)
            con.Open()
            Try
                pass = cmd.ExecuteScalar().ToString

            Catch ex As Exception
                MessageBox.Show("User Profile was not Found", "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
            End Try
            If (password = pass) Then
                MessageBox.Show("Success!")

                Borrower_Profile.Show()
                Me.Hide()

            End If

        End If

    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Me.Close()
        Loading.Show()
    End Sub

    Private Sub TextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles TextBox1.TextChanged

    End Sub
End Class