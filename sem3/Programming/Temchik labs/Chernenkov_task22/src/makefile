# makefile t22

.SUFFIXES: .class .java

PACK=t22
TARG=test
JC=javac -g
JM=java -ea -jar
JR=jar -cfe

OBJ=$(PACK)/Vector3D.class \
    $(PACK)/test.class

.java.class:
	$(JC) $<

run: build
	$(JM) $(TARG).jar

build: 	$(OBJ)
	$(JR) $(TARG).jar $(PACK).test $(OBJ)

clean:
	for %%f in ($(OBJ)) do del %%f
	del $(TARG).jar

$(PACK)/Vector3D.class: $(PACK)/Vector3D.java makefile

$(PACK)/test.class: $(PACK)/test.java makefile

# eof makefile t22