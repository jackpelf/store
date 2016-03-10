del *.class
javac -O -target 1.1 -source 1.2 -g:none ecm.java
@if errorlevel 1 goto fin
jar -cf ecm.jar ecm.class ecm$Command.class AlertContinue.class expression.class AlertActionListener.class PrimeTrialDivisionData.class PrimeSieveData.class Siqs.class factorApplet.class
ren ecm.jar ecm.jar
:fin
