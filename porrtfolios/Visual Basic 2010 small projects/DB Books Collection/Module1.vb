Imports System.Data.OleDb
Imports System
Imports ICT_2nd_Project.Database1DataSet
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Linq
Imports System.Text
Imports System.Windows.Forms
Imports System.Threading.Tasks
Imports System.Data.DataColumn
Module Module1

    Public DataColumn
    Public cmbItemValue As String
    Public cn As New OleDb.OleDbConnection
    Public dt As New DataTable
    Public cmd As New OleDbCommand
    Public da As OleDbDataAdapter
    Public ds As New DataSet
    Public ds1 As New DataSet
    Public ds2 As New DataSet
    Public str As String
    Public Sub con()
        cn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Users\ASUS K43S\AppData\Local\Temporary Projects\ICT 2nd Project\Database1.mdb"
    End Sub
End Module
