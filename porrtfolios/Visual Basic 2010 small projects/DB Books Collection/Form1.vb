Public Class Loading

    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Timer1.Start()

    End Sub

    Private Sub Timer1_Tick(sender As System.Object, e As System.EventArgs) Handles Timer1.Tick
        ProgressBar1.Increment(20)
        If ProgressBar1.Value = 100 Then
            Button1.Enabled = True
            Button2.Enabled = True
            Button3.Enabled = True
        End If
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Me.Hide()
        SignINUser.Show()



    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        Dim iexit As DialogResult
        iexit = MessageBox.Show("Are you sure you want to exit this application?", "CLose", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If iexit = DialogResult.Yes Then
            MessageBox.Show("Thank You!")
            Me.Close()
        End If
    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Me.Hide()
        Form4.Show()


    End Sub
End Class
