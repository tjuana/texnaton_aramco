object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Swarm'
  ClientHeight = 553
  ClientWidth = 1431
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 126
    Top = 5
    Width = 18
    Height = 19
    Caption = '10'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Ed: TMemo
    Left = 0
    Top = 320
    Width = 1431
    Height = 233
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
    ExplicitTop = 285
    ExplicitHeight = 136
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1431
    Height = 320
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Im: TImage
      Left = 0
      Top = 74
      Width = 1431
      Height = 240
      Align = alTop
      ExplicitTop = 37
      ExplicitWidth = 1255
    end
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 1431
      Height = 74
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
        Left = 11
        Top = 5
        Width = 31
        Height = 19
        Caption = 'Step'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 126
        Top = 5
        Width = 18
        Height = 19
        Caption = '10'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 177
        Top = 5
        Width = 27
        Height = 19
        Caption = '100'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object ToFirstBt: TSpeedButton
        Left = 242
        Top = 5
        Width = 23
        Height = 22
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFF000FFFFFF0FFFFFF000FFFFF00FFFFFF000FFFF0E0FF
          FFFF000FFF0EE0FFFFFF000FF0EEE0000000000F0EEEEEEEEEE00000EEEEEEEE
          EEE0000F0EEEEEEEEEE0000FF0EEE0000000000FFF0EE0FFFFFF000FFFF0E0FF
          FFFF000FFFFF00FFFFFF000FFFFFF0FFFFFFFFFFFFFFFFFFFFFF}
        OnClick = ToFirstBtClick
      end
      object ToLastBt: TSpeedButton
        Left = 271
        Top = 5
        Width = 23
        Height = 22
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFF000FFFFFF00FFFFF000FFFFFF0E0FFF
          F000FFFFFF0EE0FFF0000000000EEE0FF0000EEEEEEEEEE0F0000EEEEEEEEEEE
          00000EEEEEEEEEE0F0000000000EEE0FF000FFFFFF0EE0FFF000FFFFFF0E0FFF
          F000FFFFFF00FFFFF000FFFFFF0FFFFFF000FFFFFFFFFFFFFFFF}
        OnClick = ToLastBtClick
      end
      object Label5: TLabel
        Left = 307
        Top = 6
        Width = 20
        Height = 19
        Caption = 'NX'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 399
        Top = 6
        Width = 21
        Height = 19
        Caption = 'NY'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object CalcBt: TSpeedButton
        Left = 561
        Top = 6
        Width = 66
        Height = 25
        Caption = 'Calc'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = CalcBtClick
      end
      object StepSE: TCSpinEdit
        Left = 47
        Top = 2
        Width = 73
        Height = 29
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        MaxValue = 600
        MinValue = 1
        ParentFont = False
        TabOrder = 0
        Value = 1
        OnChange = StepSEChange
      end
      object UD10: TUpDown
        Left = 149
        Top = 3
        Width = 19
        Height = 26
        TabOrder = 1
        OnClick = UD10Click
      end
      object UD100: TUpDown
        Tag = 100
        Left = 207
        Top = 3
        Width = 19
        Height = 26
        Min = -10000
        Max = 10000
        TabOrder = 2
        OnClick = UD10Click
      end
      object TB: TTrackBar
        Left = 8
        Top = 44
        Width = 1409
        Height = 27
        Frequency = 10
        TabOrder = 3
        ThumbLength = 15
        OnChange = TBChange
      end
      object NXSE: TCSpinEdit
        Left = 333
        Top = 3
        Width = 59
        Height = 29
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        MaxValue = 600
        MinValue = 1
        ParentFont = False
        TabOrder = 4
        Value = 40
        OnChange = StepSEChange
      end
      object NYSE: TCSpinEdit
        Left = 425
        Top = 3
        Width = 59
        Height = 29
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        MaxValue = 600
        MinValue = 1
        ParentFont = False
        TabOrder = 5
        Value = 12
        OnChange = StepSEChange
      end
      object RB0: TRadioButton
        Left = 492
        Top = 0
        Width = 64
        Height = 17
        Caption = '40x12'
        Checked = True
        TabOrder = 6
        TabStop = True
        OnClick = RB0Click
      end
      object RB1: TRadioButton
        Tag = 1
        Left = 492
        Top = 15
        Width = 64
        Height = 17
        Caption = '80x24'
        TabOrder = 7
        OnClick = RB0Click
      end
      object RB2: TRadioButton
        Tag = 2
        Left = 492
        Top = 30
        Width = 64
        Height = 17
        Caption = '120x36'
        TabOrder = 8
        OnClick = RB0Click
      end
      object ResE: TEdit
        Left = 633
        Top = 5
        Width = 732
        Height = 27
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 9
      end
    end
  end
  object UpDown1: TUpDown
    Tag = 10
    Left = 149
    Top = 3
    Width = 19
    Height = 26
    Min = -10000
    Max = 10000
    TabOrder = 2
    OnClick = UD10Click
  end
end
