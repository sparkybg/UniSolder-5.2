Imports System.Windows.Forms
Imports System.IO

Public Class RLE

    Private FileReader As BinaryReader

    Public Function LoadFile(ByVal filepath As String) As Boolean
        Dim i As UInt32
        Dim i1 As UInt32
        Dim i2 As UInt32
        Dim rv As Boolean
        Dim inBuff() As Byte
        Dim outBuff() As Byte
        Dim outbuff2() As Byte
        Dim cCount As Byte
        Dim l As UInt32

        rv = False
        FileReader = Nothing
        'Try
        FileReader = New BinaryReader(File.OpenRead(filepath))
        l = FileReader.BaseStream.Length
        ReDim inBuff(l)
        ReDim outBuff(l)
        ReDim outbuff2(l * 2)
        FileReader.Read(inBuff, 0, l)
        FileReader.Close()

        cCount = 1
        i1 = 0
        For i = 0 To l - 1
            If inBuff(i) > 127 Then MessageBox.Show("File contains values higher than 128")
            If i < l - 1 And cCount < 127 And inBuff(i) = inBuff(i + 1) Then
                cCount = cCount + 1
            Else
                If cCount > 1 Then
                    outBuff(i1) = cCount + 128
                    i1 = i1 + 1
                End If
                outBuff(i1) = inBuff(i)
                i1 = i1 + 1
                cCount = 1
            End If
        Next i
        cCount = 1
        i2 = 0
        For i = 0 To i1 - 1
            If outBuff(i) >= 128 Then
                cCount = outBuff(i) - 128
            Else
                While cCount > 0
                    outbuff2(i2) = outBuff(i)
                    i2 = i2 + 1
                    cCount = cCount - 1
                End While
                cCount = 1
            End If
        Next i
        For i = 0 To l - 1
            If (inBuff(i) <> outbuff2(i)) Then Throw New Exception("ERROR: Streams do not match!")
        Next
        MessageBox.Show(l & " " & i1 & " " & i2)
        'Catch ex As Exception
        'End Try
        FileReader = Nothing
        Return True
    End Function
End Class
