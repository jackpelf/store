c Class Form1

    Private Sub TextBox1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox1.TextChanged

    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles encrypt.Click

        Dim str As String
        Dim ans(100) As Char
        str = TextBox1.Text
        ans = str.ToCharArray()
        Dim i As Integer
        For i = 0 To Len(str)
            If (i = Len(str)) Then
                Exit For
            End If
            Dim t As Integer
            t = Asc(ans(i))
            If (t >= 65 And t <= 90) Then
                t = 65 + ((t - 65 + 5) Mod 26)
            ElseIf (t >= 97) Then
                t = 97 + (t - 97 + 5) Mod 26
            End If
            ans(i) = Chr(t)
        Next
        TextBox2.Text = ans

    End Sub

    Private Sub TextBox2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox2.TextChanged

    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        encrypt.Text = "encrypt"
        Label1.Text = "ciphertext:"
        Label2.Text = "plaintext:"
    End Sub
End Class

