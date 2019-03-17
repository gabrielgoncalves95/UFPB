JCC = javac
JAVA = java
JFLAGS = -g

default: sortMain.class sortFunc.class

sortMain.class: sortMain.java
	$(JCC) $(JFLAGS) sortMain.java
sortFunc.class: sortFunc.java
	$(JCC) $(JFLAGS) sortFunc.java

clean:
	$(RM) *.class


