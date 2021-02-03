For Developers
============

You can also see [Java](https://github.com/starlangsoftware/ParseTree), [Python](https://github.com/starlangsoftware/ParseTree-Py), or [C#](https://github.com/starlangsoftware/ParseTree-CS) repository.

## Requirements

* [C++ Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C++ Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called ParseTree-CPP will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/ParseTree-CPP.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run TestTreeBank.cpp .

Detailed Description
============

+ [TreeBank](#treebank)
+ [ParseTree](#parsetree)

## TreeBank

To load a TreeBank composed of saved ParseTrees from a folder:

	TreeBank(File folder)

To load trees with a specified pattern from a folder of trees: 

	TreeBank(File folder, String pattern)
	
To load trees with a specified pattern and within a specified range of numbers from a folder of trees:

	TreeBank(File folder, String pattern, int from, int to)
	
the line above is used. For example,

	a = TreeBank(new File("/mypath"));

the line below is used to load trees under the folder "mypath" which is under the current folder. If only the trees with ".train" extension under the same folder are to be loaded:

	a = TreeBank(new File("/mypath"), ".train");

If among those trees, only the ones between 1 and 500 are to be loaded:

	a = TreeBank(new File("/mypath"), ".train", 1, 500);

the line below is used. 

To iterate over the trees after the TreeBank is loaded:

	for (int i = 0; i < a.size(); i++){
		ParseTree p = a.get(i);
	}
	
a block of code like this can be useful.

## ParseTree

To load a saved ParseTree:

	ParseTree(FileInputStream file)
	
is used. Usually it is more useful to load a TreeBank as explained above than loading the ParseTree one by one.

To find the node number of a ParseTree:

	int nodeCount()
	
leaf number of a ParseTree:

	int leafCount()
	
number of words in a ParseTree:

	int wordCount(boolean excludeStopWords)
	
above methods can be used.
