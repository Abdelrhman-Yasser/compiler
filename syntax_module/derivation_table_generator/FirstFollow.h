/* INCLUDE GUARD */
/****************************************/
#ifndef FIRSTFOLLOW_H_
#define FIRSTFOLLOW_H_

/* INCLUDE LIBRARIES */
/****************************************/
#include "../rule_extractor/Production.h"
#include "../rule_extractor/Node.h"
#include "../rule_extractor/GrammerParser.h"
#include <map>
#include <set>
#include <iostream>

/* CLASS DEFINITION */
/****************************************/
class First_Follow {

private:
	/* CLASS ATTRIBUTES */
	vector<Production*> rules ;
	map<string,set<Node>> first_set,follow_set ;
	map<ProductionElement*,set<Node>> first_elem_set ;
	map<string , Production*> rules_index ;
	map<string , vector<pair<Node* ,Production*> > > after_index;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	First_Follow(vector<Production*> rules);
	virtual ~First_Follow();

public:
	/* INTERFACE METHODS */
	map<ProductionElement*,set<Node>> get_first_elem() ;
	map<string,set<Node>> get_follow() ;

private:
	/* UTILITY METHODS */
	void generate_rules_index() ;
	void generate_after_index() ;
	bool has_epsilon (set<Node> first) ;
	set<Node> follow(string node) ;
	set<Node> first(Node* node) ;
	set<Node> first(Production* prod) ;
	set<Node> first(ProductionElement* prod_elem) ;


};

#endif /* FIRSTFOLLOW_H_ */
