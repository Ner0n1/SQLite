object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = VirtualStringTree1
  Caption = 'Form1'
  ClientHeight = 267
  ClientWidth = 613
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 447
    Top = 175
    Width = 79
    Height = 15
    Caption = 'Additional info'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object TLabel
    Left = 587
    Top = 196
    Width = 3
    Height = 15
  end
  object Label6: TLabel
    Left = 447
    Top = 196
    Width = 50
    Height = 15
    Caption = 'Frecency:'
  end
  object Label2: TLabel
    Left = 565
    Top = 196
    Width = 5
    Height = 15
    Caption = '-'
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 433
    Height = 217
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'Id'
        Width = 49
      end
      item
        Position = 1
        Text = 'Prefix'
        Width = 122
      end
      item
        Position = 2
        Text = 'Host'
        Width = 143
      end>
  end
  object Button1: TButton
    Left = 447
    Top = 103
    Width = 90
    Height = 26
    Caption = 'Clear Table'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 447
    Top = 135
    Width = 90
    Height = 26
    Caption = 'Exit'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 447
    Top = 39
    Width = 90
    Height = 26
    Caption = 'Load Table'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 447
    Top = 8
    Width = 90
    Height = 25
    Caption = 'Load DB'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 447
    Top = 71
    Width = 90
    Height = 26
    Caption = 'Delete Selected'
    Enabled = False
    TabOrder = 5
    OnClick = Button5Click
  end
end
