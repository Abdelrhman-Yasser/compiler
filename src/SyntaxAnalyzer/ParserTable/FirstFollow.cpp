/* INCLUDE HEADER */
/****************************************/
#include "../../../header/SyntaxAnalyzer/ParserTable/FirstFollow.h"

/* IMPLEMENT CONSTRUCTOR */
/****************************************/
FirstFollow::FirstFollow(vector<Production*> rules) {
	// TODO Auto-generated constructor stub
	this->rules = rules ;

	/*  GENERATE INDEX FOR RULES TO ACESS PRODUCTION WITH RHS NAME */
	generate_rules_index();

	/* GENERATE FIRST */
	for(Production* prod : rules){
		for(ProductionElement* elem : prod->get_RHS_elements())
			for(Node* node : elem->get_nodes())
				if(node->get_type() == Terminal || node->is_epsilon())
					first_set[node->get_name()].insert(*node) ;
		first_set[prod->get_LHS_name()] = first(prod) ;
	}

	/*  GENERATE AFTER INDEX TO GET AFTER EACH NODE IN EACH PRODUCTION */
	generate_after_index();

	for(Production* prod : rules){
		follow_set[prod->get_LHS_name()] = follow(prod->get_LHS_name()) ;
	}
}

FirstFollow::~FirstFollow() {
	// TODO Auto-generated destructor stub
}

/* IMPLEMENT INTERFACE METHODS */
/****************************************/
map<ProductionElement*,set<Node>>
FirstFollow::get_first_elem() {
	return this->first_elem_set ;
}


map<string,set<Node>>
FirstFollow::get_follow() {
	return this->follow_set ;
}

map<string,set<Node>> FirstFollow::get_first(){
	return first_set;
}

/* IMPLEMENT UTILITY METHODS */
/****************************************/
void
FirstFollow::generate_rules_index(){
	for(Production* p : rules){
		rules_index[p->get_LHS_name()] = p ;
	}
}


void
FirstFollow::generate_after_index() {
	for(Production* prod : rules){
		for(ProductionElement* elem : prod->get_RHS_elements()){
			vector<Node*> vec = elem->get_nodes() ;
			for(int i=0 ; i < (int)vec.size() ; i++){
				if(i+1 < (int)vec.size()){
					after_index[vec[i]->get_name()].push_back({prod , {elem,i} }) ;
				}else if(vec[i]->get_name() != prod->get_LHS_name()){
					after_index[vec[i]->get_name()].push_back({prod , {elem,i} }) ;
				}
			}
		}
	}
}

bool
FirstFollow::has_epsilon(set<Node> first) {
	for(Node n : first)
		if(n.is_epsilon())
			return true ;
	return false ;
}

set<Node>
FirstFollow::follow(string node) {
	Node end = Node("$",Terminal) ;
	set<Node> ret ;
	vector<pair <  Production* , pair<ProductionElement* , int> > > after = after_index[node] ;

	/* MEMORIZING NODE */
	if(follow_set.find(node) != follow_set.end())
		return follow_set[node] ;

	for(int i=0 ; i < (int)after.size() ; i++){

		vector<Node*> elem = after[i].second.first->get_nodes();
		int j = after[i].second.second;

		if(j+1 == (int)elem.size()){
			ret = follow(after[i].first->get_LHS_name()) ;
			break;
		}

		j++ ;
		while(j < (int)elem.size()){
			set<Node> tmp ;
			tmp = first_set[elem[j]->get_name()] ;
			for(Node n : tmp)ret.insert(n) ;
			if(!has_epsilon(tmp))
				j = elem.size() ;
			j++ ;
		}

		if(j != (int)elem.size() + 1){
			set<Node> res = follow(after[i].first->get_LHS_name()) ;
			for(Node n : res)ret.insert(n) ;
		}
	}

	/* Start Node has $ in Follow */
	if(node == rules[0]->get_LHS_name())
		ret.insert(end);


	/* Remove epsilons */
	set<Node> ret_without_ep ;
	for(Node n : ret)
		if(!n.is_epsilon())
			ret_without_ep.insert(n);

	/* MEMORIZING NODE */
	return follow_set[node] = ret_without_ep;

}

set<Node>
FirstFollow::first(Node* node){
	set<Node> ret ;

	/* MEMORIZING NODE */
	if(first_set.find(node->get_name()) != first_set.end())
		return first_set[node->get_name()] ;

	if(node->get_type() == Terminal)
		ret.insert(*node) ;
	else if(rules_index.find(node->get_name()) != rules_index.end())
		ret = first(rules_index[node->get_name()]) ;

	/* MEMORIZING NODE */
	return first_set[node->get_name()] = ret ;
}

set<Node>
FirstFollow::first(Production* prod){
	set<Node> ret ;
	for(ProductionElement* elem : prod->get_RHS_elements()){
		set<Node> res = first(elem) ;
		for(Node n : res )ret.insert(n) ;
	}
	return ret ;
}

set<Node>
FirstFollow::first(ProductionElement* prod_elem){
	set<Node> ret ;
	for(Node* node : prod_elem->get_nodes()){
		set<Node> res = first(node) ;
		for(Node n : res )ret.insert(n) ;
		/* FOUND FIRST IN PRODUCTION ELEM elem Stop*/
		Node tmp = (*ret.begin()) ;
		if(!has_epsilon(res))
			break ;
	}
	return first_elem_set[prod_elem] = ret ;
}