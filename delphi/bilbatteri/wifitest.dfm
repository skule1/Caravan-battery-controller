object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 336
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 48
    Top = 24
    Width = 313
    Height = 281
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object IdTCPClient1: TIdTCPClient
    BoundPort = 50
    ConnectTimeout = 0
    Host = '192.168.10.95'
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    Left = 472
    Top = 72
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 528
    Top = 168
  end
end
