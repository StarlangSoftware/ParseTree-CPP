# ParseTree-CPP

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

Kaydedilmiş ParseTreelerden oluşan bir TreeBank'ı belirli bir klasörden yüklemek için

	TreeBank(File folder)

bir klasördeki ağaçlardan ismi belirli bir örüntüye sahip ağaçları yüklemek için

	TreeBank(File folder, String pattern)
	
bir klasördeki ağaçlardan ismi belirli bir örüntüye sahip ve numaraları da belirli bir aralıkta olanları yüklemek için ise

	TreeBank(File folder, String pattern, int from, int to)
	
kullanılır. Örneğin

	a = TreeBank(new File("/mypath"));

o anda bulunan klasörün altındaki "mypath" klasörünün altındaki ağaçları yüklemek için kullanılır. Aynı klasörün altındaki sadece "train" uzantılı ağaçlar yüklenecekse, 

	a = TreeBank(new File("/mypath"), ".train");

bu ağaçlardan sadece 1 ile 500 arasındaki ağaçlar yüklenecekse de

	a = TreeBank(new File("/mypath"), ".train", 1, 500);

kullanılır.

TreeBank yüklendikten sonra ağaçlar üstünde gezmek için ise,

	for (int i = 0; i < a.size(); i++){
		ParseTree p = a.get(i);
	}
	
gibi bir kod kullanılabilir.

## ParseTree

Kaydedilmiş bir ParseTree'yi yüklemek için

	ParseTree(FileInputStream file)
	
kullanılır. Genel olarak tek tek ParseTree yüklemek yerine yukarıda anlatıldığı gibi bir TreeBank yüklemek daha mantıklıdır.

Bir ParseTree'nin düğüm sayısını

	int nodeCount()
	
yaprak sayısını 

	int leafCount()
	
içinde yer alan kelime sayısını da

	int wordCount(boolean excludeStopWords)
	
metodları ile bulabiliriz.

## Cite
If you use this resource on your research, please cite the following paper: 

```
@inproceedings{yildiz2014constructing,
  title={Constructing a {T}urkish-{E}nglish parallel treebank},
  author={Y{\i}ld{\i}z, O. T. and Solak, E. and G{\"o}rg{\"u}n, O. and Ehsani, R.},
  booktitle={Proceedings of the 52nd Annual Meeting of the Association for Computational Linguistics},
  volume={2},
  pages={112--117},
  year={2014}
}

@incollection{yildiz2015constructing,
  title={Constructing a {T}urkish constituency parse treeBank},
  author={Y{\i}ld{\i}z, O. T. and Solak, E. and {\c{C}}and{\i}r, {\c{S}}. and Ehsani, R. and G{\"o}rg{\"u}n, O.},
  booktitle={Information Sciences and Systems 2015},
  pages={339--347},
  year={2015},
  publisher={Springer}
}

@InProceedings{gorgun16,
  author    = {O. Gorgun and O. T. Yildiz and E. Solak and R. Ehsani},
  title     = {{E}nglish-{T}urkish Parallel Treebank with Morphological Annotations and its Use in Tree-based SMT},
  booktitle = {International Conference on Pattern Recognition and Methods},
  year      = {2016},
  address   = {Rome, Italy},
  pages     = {510--516}
}
