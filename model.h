/*!
 * \file model.h
 * Implementation of the MVC Model component
*/
#pragma once

#include <memory>
#include <vector>
#include <fstream>

#include <primitives.h>
#include <observer.h>

using std::vector, std::string;

//! Interface for a document class
class IDocument{
public:
	//! returns the name of the document
	virtual string GetName()=0;
	//! returns the data to read/write from/to file from the application buffer
	virtual string & GetData()=0;
};

//! Document class
class Document : public IDocument{
public:
	//! Document class constructor
	/*!
	 *  \param name name of the document (its full path) 
	 */
	Document(const string & name):_name(name){}
	//! returns the name of the document
	string GetName() override {return _name;}
	//! returns the data to read/write from/to file from the application buffer
	string & GetData() override {return data;}
private:
	string _name;
	string data;//current data
};

//! Interface for the class of an abstract factory creating document
class IDocumentFactory{
public:
	//! create new document method
	virtual std::unique_ptr<IDocument> CreateNewDocument(const string & name) = 0;
	//! import document fron file method
	virtual std::unique_ptr<IDocument> ImportDocumentFromFile(const string & name) = 0;
};

//! An abstract factory class for creating document
class DocumentFactory : public IDocumentFactory {
public:
	//! Default constructor
	DocumentFactory() = default;
	//! Create new document method
	std::unique_ptr<IDocument> CreateNewDocument(const string & name)      override {return std::make_unique<Document>(name);}
	//! Import document from file method
	std::unique_ptr<IDocument> ImportDocumentFromFile(const string & name) override {return std::make_unique<Document>(name);}
};

//!  MVC Nodel component class 
/*!
 *  \details MVC Model class
 */
class VectorRedactor_Model : public Observable {
public:
	//! VectorRedactor_Model constructor
	VectorRedactor_Model():documentFactory(std::make_unique<DocumentFactory>()){}
	//! This method is only for initial rendering of the GUI on the screen at the very start of the application
	//! @see VectorRedactor_Controller::start()
	void init(){
		//only for rerendering at the nvery beginning:
		notifyUpdate();
	}
	//! Create new document
	void CreateNewDocument(const string & name){
		documents.push_back( documentFactory->CreateNewDocument(name) );
		notifyUpdate();
	}
	//! Import document from file
	void ImportDocumentFromFile(const string & filename){
		in = std::make_unique<std::ifstream>();
		in->open(filename, std::ios::in);
		if(in->good()){
			documents.push_back( documentFactory->CreateNewDocument(filename) );
			string data_to_write = documents.back()->GetData();
			//get length of file:
    		in->seekg(0, in->end);
    		const int size = in->tellg();
    		in->seekg(0, in->beg);
			out->write(data_to_write.data(), size);
		}
		in->close();
		in.reset();
		notifyUpdate();
	}
	//! Export document to file
	void ExportDocumentToFile(const string & filename){
		out->open(filename, std::ios::out);
		if(out->good()){
			documents.push_back( documentFactory->CreateNewDocument(filename) );
			string data_to_write = documents.back()->GetData();
			out->write(data_to_write.data(), data_to_write.size());
		}
		out->close();
		out.reset();
		notifyUpdate();
	}
	//! Create a geometric primitive
	void CreatePrimitive(std::unique_ptr<IPrimitive> primitive){
		primitives.push_back(std::move(primitive));
		notifyUpdate();
	}
	//! Remove a given geometric primitive
	void RemovePrimitive(size_t index){
		primitives.erase(primitives.begin()+index);
		notifyUpdate();
	}
	//! Get the most newly created geometric primitive and remove it from the screen
	std::unique_ptr<IPrimitive> GetLastPrimitive(){
		auto temp = std::move(primitives.back());
		primitives.pop_back();
		return temp;
	}
	//! Get number of currently opened documents
	size_t NumberOfOpenedDocuments() const {return documents.size();}
	//! Get the current number of geometric primitives on the screen
	size_t GetPrimitivesSize() const {return primitives.size();}
private:
	std::unique_ptr<std::ifstream> in;
	std::unique_ptr<std::ofstream> out;
	vector<std::unique_ptr<IDocument>> documents;
	std::unique_ptr<IDocumentFactory> documentFactory;
	vector<std::unique_ptr<IPrimitive>> primitives;
};