[Rainmeter]
OnRefreshAction=[!CommandMeasure NetAnimation "Execute [&ActionList]"]

[Variables]
NetValue=0

[ActionList]
Measure=Calc
Formula=1+#BatterySaverMode#

[NoneMeasure]
Measure=Calc
Formula=-1

[NetBytes]
Measure=Plugin
Plugin=UsageMonitor
Category=Network Interface
Counter=Bytes total/sec
MinValue=0
MaxValue=100
UpdateDivider=(#BatterySaverMode# = 0 ? 10 : 20)
OnChangeAction=[!UpdateMeasure NetRounded]

; [NetWidth]
; Measure=Plugin
; Plugin=UsageMonitor
; Category=Network Interface
; Counter=Current bandwidth
; MinValue=0
; MaxValue=100
; UpdateDivider=3600
; OnChangeAction=[!UpdateMeasure NetRounded]

[NetRounded]
Measure=Calc
Formula=Round(Clamp(NetBytes * 8 / #NetWidth# * 100, 0, 100),0)
MinValue=0
MaxValue=100
IfCondition=(NetMeasure < #YellowStarts#)
IfTrueAction=[!SetVariable NetColor #GreenColor#]
IfCondition2=(NetMeasure >= #YellowStarts#) && (NetMeasure < #RedStarts#)
IfTrueAction2=[!SetVariable NetColor #YellowColor#]
IfCondition3=(NetMeasure >= #RedStarts#)
IfTrueAction3=[!SetVariable NetColor #RedColor#]
OnChangeAction=[!CommandMeasure NetAnimation "Stop [&ActionList]"][!CommandMeasure NetAnimation "Execute [&ActionList]"]

[NetMeasure]
Measure=NetIn
UseBits=1
; Measure=Calc
; Formula=#NetValue#
; MinValue=0
; MaxValue=100
; DynamicVariables=1

[NetAnimation]
Measure=Plugin
Plugin=ActionTimer
ActionList1=Repeat AddStep, 100, 10
ActionList2=Update
AddStep=[!SetVariable NetValue ([#NetValue]+([&NetRounded:]-[#NetValue])/2)][!UpdateMeasure NetMeasure]
Update=[!SetVariable NetValue [&NetRounded:]][!UpdateMeasure NetMeasure]
DynamicVariables=1
