// vim:tabstop=4:shiftwidth=4:noexpandtab:textwidth=80
/*
 * $RCSfile$
 *
 * $Log$
 * Revision 1.59  2006/06/09 17:17:33  hockm0bm
 * * PageTreeNodeType enum added
 * * getPageTreeRoot, getNodeType, getKidsCount, getKidsFromInterNode helper
 *   methods added
 * * findPageDict and searchTreeNode methods rewritten
 * 	- not depended on Count field anymore
 * 	- more error prone
 * 	- throws only when neccessary (no falback possible)
 * * CPdf::getDictionary changed to const
 * * CPdf::getPageCount reimplemented
 * 	- calculates page count rather than use Pagetree root Count field which
 *           may be malformed
 * 	- doesn't throw
 * * getNodePosition, searchTreeNode, getNodePosition signature changed
 * 	- pdf is const reference
 *
 * Revision 1.58  2006/06/05 15:19:36  hockm0bm
 * CPdf::registerIndirectProperty
 *         - sets this pdf before _makeXpdfObject and restores original after
 *           (so xref in created object is set correctly)
 *
 * Revision 1.57  2006/06/05 09:12:28  hockm0bm
 * locChange is used on cloned values which require indiref
 *
 * Revision 1.56  2006/06/05 08:57:32  hockm0bm
 * refactoring CObjectSimple
 *         - getPropertyValue -> getValue
 *         - writeValue -> setValue
 *
 * Revision 1.55  2006/06/05 06:27:01  hockm0bm
 * * CPdf::subsReferencies
 *         - substitues also referencie also for streams
 * * CPage::insertPage
 *         - handles page from different file correctly
 *
 * Revision 1.54  2006/06/02 16:51:21  hockm0bm
 * typo fix
 *
 * Revision 1.53  2006/06/02 16:38:15  hockm0bm
 * modecontroller field has not been initialized in constructors
 *         - thx to Jozo
 *
 * Revision 1.52  2006/05/23 19:07:22  hockm0bm
 * debug messages improved
 *
 * Revision 1.51  2006/05/15 18:30:23  hockm0bm
 * * isEncrypted bug fixed
 *         - Encrypt can be also reference to dictionary
 * * isDecrypted declaration removed from header file
 *
 * Revision 1.50  2006/05/14 12:37:24  hockm0bm
 * debug messages improved
 *
 * Revision 1.49  2006/05/13 22:19:29  hockm0bm
 * isInValidPdf refactored to hasValidPdf or isPdfValid functions
 *
 * Revision 1.48  2006/05/13 21:36:52  hockm0bm
 * * addIndirectProperty reworked (problem with cyclic reference dependencies)
 *         - new followsRef flag
 *         - throws if given ip is reference
 * * addProperty, subsReferencies, createMapping methods added
 * * addReferencies replaced by subsReferencies
 * * doc update
 *
 * Revision 1.47  2006/05/10 21:09:26  hockm0bm
 * isChanged meaning changed
 *         - returns true if there are any chnages after last save (or pdf creation)
 *         - doesn't check current revision
 *
 * Revision 1.46  2006/05/10 20:23:50  hockm0bm
 * * isChange bug fixed
 * 	- change class field is initialized in constructor now
 * * new CPdf::getTrailer
 * * new utils::isEncrypted method
 *
 * Revision 1.45  2006/05/09 20:05:19  hockm0bm
 * minor changes
 *
 * Revision 1.44  2006/05/06 08:38:19  hockm0bm
 * * CPdf constructor sets mode of xref according its mode
 * * CPdf::consolidatePageList bug fixed
 * 	- readdContainer has to contain all pages with pos >= minPos (not only >)
 *
 * Revision 1.43  2006/05/05 11:55:55  petrm1am
 *
 * Commiting changes sent by Michal:
 *
 * cpdf.cc:
 * * consolidatePageList bug fixed
 *     - difference += pageCount not -=
 * * debug messages improved
 *
 * cxref.cc:
 * * reserveRef bug fix
 *     - totalCount replaced by xrefCount from XRef::getNumObjects
 *     - num is initialized to -1
 *     - kernelPrintDbg message wrong position (cannot use new entry)
 *
 * Revision 1.42  2006/05/01 13:53:07  hockm0bm
 * new style printDbg
 *
 * Revision 1.41  2006/04/28 17:15:50  hockm0bm
 * * helper functions exported by header file now
 *
 * Revision 1.40  2006/04/27 18:29:10  hockm0bm
 * * all methods which could be set to const are const now
 * * pageList is mutable to enable getPage (and all depended in getPage)
 *   to be const methods
 * * pageCount is mutable to enable getPageCount to be conts
 * * methods which should fail in read-only mode doesn't compare mode
 *   directly but use getMode - because it consideres also current revision
 * * changeIndirectProperty bug fixed - checking for mode is done now
 *
 * Revision 1.39  2006/04/27 05:55:39  hockm0bm
 * * changeRevision implemented
 * * documentation update
 *
 * Revision 1.38  2006/04/23 15:12:58  hockm0bm
 * changeIndirectProperty behaviour changed
 *         - indirect mapping removed only if given property is different
 *           instance than given one
 *         - throws CObjInvalidObject exception is thrown if prop is not from this
 *           pdf or mapping doesn't exist
 *
 * Revision 1.37  2006/04/23 13:14:02  hockm0bm
 * clone method implemented
 *
 * Revision 1.36  2006/04/22 20:12:50  hockm0bm
 * Last commit was accident
 * getInstance catches exceptions possibly thrown in CPdf and throws
 *         PdfOpenException
 *
 * Revision 1.35  2006/04/22 20:07:08  hockm0bm
 * bug fix
 *         - getPrevPage, getNextPage didn't return true if successful
 *
 * Revision 1.34  2006/04/22 17:22:14  hockm0bm
 * * getPageCount caches/uses value to/from pageCount field
 * * getNextPage, getPrevPage boundary checking corrected
 *
 * Revision 1.33  2006/04/21 20:40:02  hockm0bm
 * * changeIndirectProperty use freeXpdfObject with out problems
 * * PageTreeWatchDog::notify bug fix
 * 	- if newValue is CNull page tree consolidation wasn't done.
 * 	  Uses oldValue parent if new value is CNull
 * 	- additional checking for proper old and new values
 * 	- code reorganization and simplification
 * * caches page number in field pageCount
 * 	- invalidation is done in consolidatePageTree and initRevisionSpecific
 *
 * Revision 1.32  2006/04/20 22:34:37  hockm0bm
 * freeXpdfObject cloning seems to be problem (for array - TODO solve)
 *         - just to prevent SEGV (this solution means memmory leak)
 *
 * Revision 1.31  2006/04/20 18:04:36  hockm0bm
 * ambigues spell error corrected
 *
 */
#include <errno.h>
#include "static.h"

#include "iproperty.h"
#include "cobject.h"
#include "cobjecthelpers.h"
#include "cpdf.h"
#include "factories.h"
#include "utils/debug.h"

using namespace boost;
using namespace std;
using namespace debug;

// TODO exceptions unification

typedef std::vector<boost::shared_ptr<pdfobjects::IProperty> > ChildrenStorage;

namespace pdfobjects
{

namespace utils 
{

/** Type enumeration for page tree nodes.
 * Type of dictionary in page tree. Possible values are:
 * <ul>
 * <li>ErrorNode - node has bad type (it is not dictionary or reference to
 * dictionary).
 * <li>UnknownNode - node is dictionary but it is not possible to get node type 
 * <li>LeafNode - leaf tree node (Page dictionary).
 * <li>InterNode - intermediate node (Pages dictionary).
 * <li>RootNode - intermediate root node.
 * </ul>
 *
 * <p>
 * Implementation node:<br>
 * Note that order is significant, because we assume that everything lower than
 * LeafNode is kind of error (problem) and also that greater or equal than
 * InterNode is intermediate node.
 */
enum PageTreeNodeType { ErrorNode, UnknownNode, LeafNode, InterNode, RootNode };

/** Operator for output stream with PageTreeNodeType enumeration type.
 * @param stream Stream, where to print.
 * @param nodeType type to print.
 *
 * Prints human readable from of page tree node enumeration value.
 *
 * @return reference to given stream.
 */
ostream & operator<<(ostream & stream, PageTreeNodeType nodeType)
{
	switch(nodeType)
	{
		case InterNode:
			stream << "InterNode";
			break;
		case LeafNode:
			stream << "LeafNode";
			break;
		case RootNode:
			stream << "RootNode";
			break;
		case UnknownNode:
			stream << "UnknownNode";
			break;
		case ErrorNode:
			stream << "ErrorNode";
			break;
	}

	return stream;
}

/** Gets page tree root node dictionary.
 * @param pdf Pdf where to search.
 *
 * Gets Pages field from pdf dictionary and dereference it to dictionary. If it
 * is not reference or target object is not a dictionary, returns NULL
 * dictionary.
 * <br>
 * Note that this function never throws.
 *
 * @return Dictionary wrapped by shared_ptr (NULL dictionary if not found).
 */
shared_ptr<CDict> getPageTreeRoot(const CPdf & pdf)
{
	shared_ptr<CDict> result;
	
	try
	{
		shared_ptr<IProperty> pagesProp=pdf.getDictionary()->getProperty("Pages");
		if(!isRef(pagesProp))
			// returns null dictionary
			return result;

		return getCObjectFromRef<CDict, pDict>(pagesProp);
	}catch(CObjectException & e)
	{
	}

	// returns null dictionary
	return result;
}

/** Checks given node property for its page tree node type.
 * @param nodeProp Node property (must be dictionary or reference to
 * dictionary).
 *
 * Gets node dictionary in first step (either directly from parameter or
 * dereference). If not able to get it, returns ErrorNode type. Then checks
 * whether node dictionary is same as Page tree root node and if so, returns
 * RootNode type. If not able to get root node, returns UnknownNode.
 * <br>
 * Checks for Type field in node dictionary and if present, checks its value. It
 * must be name object. If so and value is Page, returns LeafNode, or if value
 * is Pages, returns InterNode. Otherwise returns (also if Type field type is
 * not name), returns UnknownNode.
 * <br>
 * Finally tries to determine node type from existing fields. If dictionary
 * contains Kids array, it is considered to be InterNode. Otherwise returns
 * UnknownNode.
 * <br>
 * Note that this function never throws.
 *
 * @return Node type.
 */
PageTreeNodeType getNodeType(const boost::shared_ptr<IProperty> & nodeProp)
{
	PageTreeNodeType nodeType=UnknownNode;

	// checks nodeProp - must be dictionary or reference to dictionary
	shared_ptr<CDict> nodeDict;
	if(isDict(nodeProp))
		nodeDict=IProperty::getSmartCObjectPtr<CDict>(nodeProp);
	else
		if(isRef(nodeProp))
		{
			try
			{
				nodeDict=getCObjectFromRef<CDict, pDict>(nodeProp);
			}catch(ElementBadTypeException & e)
			{
				// target is not a dictionary
				return ErrorNode;
			}
		}
		else
			// property is not dictionary nor reference
			return ErrorNode;
	
	// checks root node at first
	CPdf * pdf=nodeProp->getPdf();
	assert(pdf);
	shared_ptr<CDict> rootDict=getPageTreeRoot(*pdf);
	if(rootDict==nodeDict)
		// root dictionary found and it is same as internode
		return RootNode;
		
	
	// given node is not root of page tree, chcecks Type field
	if(nodeDict->containsProperty("Type"))
	{
		shared_ptr<IProperty> nodeType=nodeDict->getProperty("Type");
		try
		{
			if(isRef(nodeType))
				nodeType=getCObjectFromRef<CName,pName>(nodeType);
			CName::Value typeName=getValueFromSimple<CName, pName, CName::Value>(nodeType);
			if(typeName=="Page")
				return LeafNode;
			if(typeName=="Pages")
				return InterNode;
		}catch(CObjectException & e)
		{
			// bad typed field
		}
		
		return UnknownNode;
	}

	// type field not found, so tries to determine dictionary type according
	// existing fields.
	// Internode should contain at least Kids array field
	if(nodeDict->containsProperty("Kids"))
	{
		shared_ptr<IProperty> kidsProp=nodeDict->getProperty("Kids");
		if(isArray(kidsProp))
			return InterNode;
	}

	// TODO how to determine leaf node? (most of required fields can't be used
	// because of their inheritance)
	
	return nodeType;
}

/** Collects all kids elements from internode dictionary.
 * @param interNodeDict Intermediate node dictionary.
 * @param container Container where to store kids.
 *
 * Clears given container at first. Gets Kids array from given dictionary and
 * adds all its elements to given container. If not able to do so, immediatelly
 * returns. Given container is empty if no kid is found (or any other problem
 * occures).
 * <br>
 * Container template type must store shared_ptr<IProperty> types and support
 * clear and push_back methods.
 * <br>
 * Note that this function never throws.
 */
template<typename Container>
void getKidsFromInterNode(const boost::shared_ptr<CDict> & interNodeDict, Container & container)
{
	container.clear();

	// tries to get Kids array
	if(interNodeDict->containsProperty("Kids"))
	{
		shared_ptr<IProperty> kidsProp=interNodeDict->getProperty("Kids");
		shared_ptr<CArray> kidsArray;
		if(isRef(kidsProp))
		{
			try
			{
				kidsArray=getCObjectFromRef<CArray, pArray>(kidsProp);
			}catch(CObjectException & e)
			{
				// target is not an array
				return;
			}
		}else
		{
			if(!isArray(kidsProp))
				// not an array
				return;
			kidsArray=IProperty::getSmartCObjectPtr<CArray>(kidsProp);
		}
		
		// collects all children to given container
		for(size_t i=0; i<kidsArray->getPropertyCount(); i++)
			container.push_back(kidsArray->getProperty(i));
	}

}

/** Calculates number of direct pages under given node property.
 * @param interNodeProp Page tree node property (must be dictionary or reference
 * to dictionary).
 *
 * Checks whether given node is LeafNode and if so, immediatelly returns with 1
 * (page contains one direct page node). Otherwise tries to get node dictionary
 * from given property. If not able to do so, returns 0, because this node is
 * probably invalid and so it can't contain any direct page node. Finally
 * collects all Kids elements from dictionary (uses getKidsFromInterNode
 * function) and calls this function recursively on each. Collected number is
 * returned.
 * <br>
 * Note that this function never throws.
 *
 */
size_t getKidsCount(const boost::shared_ptr<IProperty> & interNodeProp)
{	
	// leaf node adds one direct page in page tree
	if(getNodeType(interNodeProp)==LeafNode)
		return 1;

	// gets dictionary from given property. If reference, gets target object. If
	// it is not a dictionary, returns with 0
	shared_ptr<CDict> interNodeDict;
	if(isRef(interNodeProp))
	{
		try
		{
			interNodeDict=getCObjectFromRef<CDict, pDict>(interNodeProp);
		}catch(CObjectException & e)
		{
			// target is not a dictionary
			return 0;
		}
	}else
	{
		if(!isDict(interNodeProp))
			return 0;
		interNodeDict=IProperty::getSmartCObjectPtr<CDict>(interNodeProp);
	}
	
	// we assume inter node, so collects all children and calculates total
	// direct page count (calls recursively)
	ChildrenStorage children;
	size_t count=0;
	getKidsFromInterNode(interNodeDict, children);
	for(ChildrenStorage::const_iterator i=children.begin(); i!=children.end(); i++)
		count+=getKidsCount(*i);

	return count;
}

boost::shared_ptr<CDict> findPageDict(const CPdf & pdf, boost::shared_ptr<IProperty> pagesDict, size_t startPos, size_t pos)
{
	utilsPrintDbg(DBG_DBG, "startPos=" << startPos << " pos=" << pos);
	if(startPos > pos)
	{
		utilsPrintDbg(DBG_ERR, "startPos > pos");
		// impossible to find such page
		throw PageNotFoundException(pos);
	}

	// dictionary smart pointer holder
	// it is initialized according pagesDict parameter - if it is reference
	// it has to be dereferenced
	shared_ptr<CDict> dict_ptr;

	// checks if given parameter is reference and if so, dereference it
	// using getIndirectProperty method and casts to dict_ptr
	// otherwise test if given type is dictionary and casts to dict_ptr
	if(isRef(pagesDict))
	{
		utilsPrintDbg(DBG_DBG, "pagesDict is reference");
		try
		{
			dict_ptr=getCObjectFromRef<CDict, pDict>(pagesDict);
		}catch(ElementBadTypeException & e)
		{
			// malformed pdf
			utilsPrintDbg(DBG_ERR, "pagesDict doesn't refer to dictionary");
			throw ElementBadTypeException("pagesDict");
		}
	}else
	{
		if(!isDict(pagesDict))
		{
			utilsPrintDbg(DBG_ERR, "pagesDict is not dictionary type="<< pagesDict->getType());
			// maloformed pdf
			throw ElementBadTypeException("pagesDict");
		}
		dict_ptr=IProperty::getSmartCObjectPtr<CDict>(pagesDict);
	}

	// gets dictionary node type
	PageTreeNodeType nodeType=getNodeType(dict_ptr);
	
	// if type is Page then we have page dictionary and so start_pos and pos 
	// must match otherwise it is not possible to find page at given position
	if(nodeType==LeafNode)
	{
		utilsPrintDbg(DBG_DBG, "Page node is direct page");
		// everything ok 
		if(startPos == pos)
		{
			utilsPrintDbg(DBG_INFO, "Page found");
			return dict_ptr;
		}
		
		// unable to find
		utilsPrintDbg(DBG_ERR, "Page not found startPos="<<startPos);
		throw PageNotFoundException(pos);
	}

	// internode or root node
	if(nodeType>=InterNode)
	{
		utilsPrintDbg(DBG_DBG, "Page node is intermediate");

		// calculates direct page count under this inter node rather than use
		// Count field (which may be malformed)
		int count=getKidsCount(dict_ptr);

		utilsPrintDbg(DBG_DBG, "InterNode has " << count << " pages");

		// check if this subtree contains enought direct pages 
		if(count + startPos <= pos )
		{
			utilsPrintDbg(DBG_ERR, "page can't be found under this subtree startPos=" << startPos);
			// no way to find given position under this subtree
			throw PageNotFoundException(pos);
		}

		// PAGE IS IN THIS SUBTREE, we have to find where
		
		// gets Kids array from pages dictionary and gets all its children
		ChildrenStorage children;
		getKidsFromInterNode(dict_ptr, children);

		// min_pos holds minimum position for actual child (at the begining
		// startPos value and incremented by page number in node which can't
		// contain pos (normal page 1 and Pages their count).
		ChildrenStorage::iterator i;
		size_t min_pos=startPos, index=0;
		for(i=children.begin(); i!=children.end(); i++, index++)
		{
			shared_ptr<IProperty> child=*i;

			if(!isRef(child))
			{
				utilsPrintDbg(DBG_WARN, "Kid["<<index<<"] is not reference. type="<<child->getType()<<". Ignoring");
				continue;
			}
			
			// all members of Kids array have to be either intermediate nodes or
			// leaf nodes - all other are ignored
			PageTreeNodeType nodeType=getNodeType(child);
			if(nodeType!=InterNode && nodeType!=LeafNode)
			{
				utilsPrintDbg(DBG_WARN, "Kid["<<index<<"] is not valid page tree node. nodeType="<<nodeType<<". Ignoring");
				continue;
			}

			// gets child dictionary (everything is checked, so no exception can
			// be thrown here)
			shared_ptr<CDict> child_ptr=getCObjectFromRef<CDict, pDict>(child); 
			
			utilsPrintDbg(DBG_DBG, "kid node type="<<nodeType);

			// Page dictionary (leaf node) is ok if min_pos equals pos, 
			// otherwise it is skipped - can't use recursion here because it's
			// not an error that this page is not correct one (recursion would
			// throw an exception)
			// min_pos is incremented if this page is not searched one
			if(nodeType==LeafNode)
			{
				if(min_pos == pos)
				{
					utilsPrintDbg(DBG_INFO, "page at pos="<<pos<<" found");
					return child_ptr;
				}
				min_pos++;
				continue;
			}

			// Pages dictionary is checked for its page count and if pos can
			// be found there, starts recursion - value is calculated rather
			// than used from Count field (which may be malformed).
			// Otherwise increment min_pos with its count and continues
			if(nodeType==InterNode)
			{
				int count=getKidsCount(child_ptr);

				if(min_pos + count > pos )
					// pos IS in this subtree
					return findPageDict(pdf, child_ptr, min_pos, pos);

				// pos is not in this subtree
				// updates min_pos with its count and continues
				min_pos+=count;

				continue;
			}
		}
		assert(!"Never can get here. Possibly bug!!!");
	}
	
	// should not happen - malformed pdf document
	utilsPrintDbg(DBG_ERR, "pagesDict dictionary is not valid page tree node. Nodetype="<<nodeType);
	throw ElementBadTypeException("pagesDict");
}

/** Searches node in page tree structure.
 * @param pdf Pdf where to search.
 * @param superNode Node which to search.
 * @param node Node to be found.
 * @param startValue Position for first found node in this superNode.
 *
 * At first checks if node and superNode are same nodes (uses == operator to
 * compare). Then tries to get Type of the superNode dictionary. In Page case 
 * returns with startValue if given nodes are same or 0 (page not found).
 * If type is Pages (intermediate node) goes through Kids array and recursively
 * calls this method for each element until recursion returns with non 0 result.
 * This means the end of recursion. startValue is actualized for each Kid's
 * element (Page element increases 1, Pages number of direct pages under node -
 * value of getKidsCount for internode).
 * <br>
 * If node is found as direct Kids member (this means that reference of target 
 * node is direct member of Kids array), then determines if the node position 
 * is unambiguous - checks whether reference to the node is unique in Kids array. 
 * If not throws exception. This means that searchTreeNode function is not able 
 * to definitively determine node's position.
 * <br>
 * Function tries to find node position also in page tree structure which 
 * doesn't follow pdf specification. All wierd page tree elements are ignored 
 * and just those which may stand for intermediate or leaf nodes are condidered.
 * Also doesn't use Count and Parent fields information during searching.
 *
 * @throw AmbiguousPageTreeException if page tree is ambiguous and node position
 * can't be determined.
 *
 * @return Position of the node or 0 if node couldn't be found under this
 * superNode.
 */
size_t searchTreeNode(const CPdf & pdf, shared_ptr<CDict> superNode, shared_ptr<CDict> node, size_t startValue)
{
	size_t position=0;

	utilsPrintDbg(DBG_DBG, "startPos="<<startValue);
	
	// if nodes are same, startValue is returned.
	if(superNode==node)
	{
		utilsPrintDbg(DBG_DBG, "Page found");
		return startValue;
	}

	// gets super node type
	PageTreeNodeType superNodeType=getNodeType(superNode);
	
	// if type is Page we return with 0, because node is not this superNode and
	// there is nowhere to go
	if(superNodeType==LeafNode)
		return 0;

	// if node is not also intermediate node (or root node) - page tree is not 
	// well formated and we skip this node
	if(superNodeType<InterNode)
	{
		utilsPrintDbg(DBG_WARN, "Given dictionary is not correct page tree node. type="<<superNodeType);
		return 0;
	}

	// given node is intermediate and so searches recursivelly all its kids
	// until first returns successfully
	ChildrenStorage children;
	ChildrenStorage::iterator i;
	getKidsFromInterNode(superNode, children);
	size_t index=0;
	for(i=children.begin(); i!=children.end(); i++, index++)
	{
		shared_ptr<IProperty> child=*i;
		
		// each element has to be reference
		if(!isRef(child))
		{
			// we will just print warning and skips this element
			utilsPrintDbg(DBG_WARN, "Kids["<<index<<"] is not an reference. type="<<child->getType()<<". Ignoring");
			continue;
		}

		// ignores also all non leaf and non intermediates nodes
		PageTreeNodeType nodeType=getNodeType(child);
		if(nodeType!=LeafNode && nodeType!=InterNode)
		{
			utilsPrintDbg(DBG_WARN, "Kids["<<index<<"] is not valid page tree element. type="<<nodeType<<". Ignoring");
			continue;
		}

		// dereference target dictionary
		shared_ptr<CDict> elementDict_ptr=getCObjectFromRef<CDict, pDict>(child);
	
		// compares elementDict_ptr (kid) with node, if they are same, returns
		// startValue
		if(elementDict_ptr==node)
		{
			position=startValue;
			break;
		}

		// recursively checks subnode - if found re-return position
		if((position=searchTreeNode(pdf, elementDict_ptr, node, startValue)))
			break;

		// node is not under elementDict_ptr node so updates startValue
		// according skipped page count (page is 1 and intermediate node the
		// number of direct pages under it)
		PageTreeNodeType childType=getNodeType(elementDict_ptr);
		if(childType==LeafNode)
		{
			// this was not correct one startValue is increased
			startValue++;
			continue;
		}
		if(childType==InterNode)
		{
			startValue+=getKidsCount(elementDict_ptr);
			continue;
		}
		
		assert(!"Never can get here. Possibly bug!!!");
	}

	// TODO ambiguous check
	return position;
}

size_t getNodePosition(const CPdf & pdf, shared_ptr<IProperty> node)
{
	utilsPrintDbg(DBG_DBG, "");
	// node must by from given pdf
	if(node->getPdf()!=&pdf)
	{
		utilsPrintDbg(DBG_ERR, "Node is not from given pdf isntance.");
		throw PageNotFoundException(0);
	}
	
	// gets page tree root - if not found, then PageNotFoundException is thrown
	shared_ptr<CDict> rootDict_ptr=getPageTreeRoot(pdf);
	if(!rootDict_ptr.get())
		throw PageNotFoundException(0);
	

	// gets dictionary from node parameter. It can be reference and
	// dereferencing has to be done or direct dictionary - otherwise error is
	// reported
	PropertyType nodeType=node->getType();
	if(nodeType!=pRef && nodeType!=pDict)
	{
		utilsPrintDbg(DBG_ERR, "Given node is not reference nor dictionary. type="<<nodeType);
		throw ElementBadTypeException("node");
	}
	shared_ptr<CDict> nodeDict_ptr;
	if(nodeType==pRef)
		nodeDict_ptr=getCObjectFromRef<CDict, pDict>(node);
	else
		nodeDict_ptr=IProperty::getSmartCObjectPtr<CDict>(node);
		
	utilsPrintDbg(DBG_DBG, "Starts searching");
	size_t pos=searchTreeNode(pdf, rootDict_ptr, nodeDict_ptr, 1);
	utilsPrintDbg(DBG_DBG, "Searching finished. pos="<<pos);
	if(pos)
		return pos;

	// node not found
	throw PageNotFoundException(0);
}

bool isDescendant(CPdf & pdf, IndiRef parent, shared_ptr<CDict> child)
{
using namespace utils;

	if(!child->containsProperty("Parent"))
	{
		// child has no parent, so can't be descendant
		return false;
	}
	
	// gets reference of parent
	IndiRef directParent=getRefFromDict("Parent", child);

	// we have direct parent reference
	// if it is same as given parent, we are done and return true
	if(parent==directParent)
		return true;

	// parent may be somewhere higher in the page tree
	// Gets direct parent indirect object from given pdf and checks its type
	// if it is NOT dictionary - we have malformed pdf - exception is thrown
	// otherwise starts recursion with direct parent dictionary
	shared_ptr<IProperty> directParent_ptr=pdf.getIndirectProperty(directParent);
	if(!isDict(directParent_ptr))
		throw MalformedFormatExeption("Page node parent field doesn't point to dictionary");
	return isDescendant(pdf, parent, IProperty::getSmartCObjectPtr<CDict>(directParent_ptr));
}

/** Registers page tree observer.
 * @param ref Reference to page tree node.
 * @param observer Pointer to observer to register.
 *
 * Registers given observer to given reference. Then gets indirect property from
 * reference and if it is Pages dictionary, Registers observer also on Kids
 * array and recursively to all its elements (which are referencies).
 */
void registerPageTreeObserver(boost::shared_ptr<CRef> ref, shared_ptr<const observer::IObserver<IProperty> > observer)
{
using namespace boost;
using namespace std;
using namespace pdfobjects::utils;

	IndiRef indiRef=getValueFromSimple<CRef, pRef, IndiRef>(ref);
	utilsPrintDbg(DBG_DBG, indiRef);

	// registers observer for page tree handling
	ref->registerObserver(observer);
	
	// dereferences and if it is Pages dictionary, calls recursively to all
	// children
	shared_ptr<CDict> dict_ptr=getDictFromRef(ref);
	string dictType=getNameFromDict("Type", dict_ptr);

	// if this is not pages dictionary, immediately returns
	if(dictType!="Pages")
		return;

	utilsPrintDbg(DBG_DBG, "Intermediate node. Registers to Kids array and all its elements");

	// gets Kids field from dictionary and all children from array and 
	// registers observer to array and to each member reference
	shared_ptr<IProperty> kidsProp_ptr=dict_ptr->getProperty("Kids");
	if(kidsProp_ptr->getType()!=pArray)
	{
		// Kids is not an array - this is not an hard error at this context
		utilsPrintDbg(DBG_WARN, "Kids field is not an array. type="<<kidsProp_ptr->getType());
		return;
	}
	shared_ptr<CArray> kids_ptr=IProperty::getSmartCObjectPtr<CArray>(kidsProp_ptr);
	kids_ptr->registerObserver(observer);
	vector<shared_ptr<IProperty> > container;
	kids_ptr->_getAllChildObjects(container);
	for(vector<shared_ptr<IProperty> >::iterator i=container.begin(); i!=container.end(); i++)
	{
		// all reference kids are used for recursion call
		shared_ptr<IProperty> elemProp_ptr=*i;
		if(elemProp_ptr->getType()==pRef)
			registerPageTreeObserver(IProperty::getSmartCObjectPtr<CRef>(elemProp_ptr), observer);
	}

	utilsPrintDbg(DBG_DBG, "All subnodes done for "<<indiRef);
}

bool isEncrypted(CPdf & pdf, string * filterName)
{
	utilsPrintDbg(DBG_DBG, "");

	// gets trailer dictionary and Encrypt entry
	shared_ptr<const CDict> trailer=pdf.getTrailer();
	try
	{
		shared_ptr<IProperty> encryptProp=trailer->getProperty("Encrypt");
		if(isRef(*encryptProp))
		{
			IndiRef ref=getValueFromSimple<CRef, pRef, IndiRef>(encryptProp);
			utilsPrintDbg(DBG_DBG, "Encrypt is reference. "<<ref);
			encryptProp.reset();
			encryptProp=pdf.getIndirectProperty(ref);
		}
		if(isDict(*encryptProp))
		{
			shared_ptr<CDict> encryptDict=IProperty::getSmartCObjectPtr<CDict>(encryptProp);
			utilsPrintDbg(DBG_INFO, "Document content contains Encrypt dictionary.");
			// if filterName parameter is non NULL, set its value to encryption
			// algorithm 
			if(filterName)
			{
				shared_ptr<IProperty> filter=encryptDict->getProperty("Filter");
				filter->getStringRepresentation(*filterName);
				utilsPrintDbg(DBG_DBG, "Encrypt uses "<<filterName<<" filter method.");
			}
			return true;
		}else
			utilsPrintDbg(DBG_WARN, "Encrypt entry found in trailer but it is not a dictionary.");
	}catch(ElementNotFoundException & e)
	{
		// no Encrypt entry
	}

	utilsPrintDbg(DBG_DBG, "Document content is not encrypted.");
	return false;
}

} // end of utils namespace

void CPdf::PageTreeWatchDog::notify(boost::shared_ptr<IProperty> newValue, boost::shared_ptr<const observer::IChangeContext<IProperty> > context) const throw()
{
using namespace observer;
using namespace boost;
using namespace debug;
using namespace utils;

	kernelPrintDbg(DBG_DBG, "");
	
	// if not basic context type, does notnig
	if(context->getType()!=IChangeContext<IProperty>::BasicChangeContextType)
		return;

	// gets basic context shared_ptr
	shared_ptr<const BasicChangeContext<IProperty> > basicContext=
		dynamic_pointer_cast<const BasicChangeContext<IProperty>, const IChangeContext<IProperty> >(context); 

	// gets original value
	const shared_ptr<IProperty> oldValue=basicContext->getOriginalValue();

	PropertyType oldType=oldValue->getType(),
				 newType=newValue->getType();

	// one of values can be CNull, but not both. If this happens, there is
	// nothing to do
	if(oldType==pNull && newType==pNull)
	{
		kernelPrintDbg(DBG_WARN, "Both newValue and oldValue are CNull");
		return;
	}
	
	// if both of values are not CRef, there is also nothing to consolidate,
	// because old mess has been replaced by new mess
	// FIXME what if whole array is deleted or replaced
	if(oldType!=pRef && newType!=pRef)
	{
		kernelPrintDbg(DBG_INFO, "Nothing to consolidate because newValue and oldValue are not CRef");
		return;
	}
		
	// if newValue is CRef instance, registers this observer on it and if it 
	// is intermediate node, also to all children. 
	// Uses registerPageTreeObserver method
	if(newType==pRef)
	{
		shared_ptr<CRef> newValueRef_ptr=IProperty::getSmartCObjectPtr<CRef>(newValue);
		try
		{
			registerPageTreeObserver(newValueRef_ptr, pdf->pageTreeWatchDog);
		}catch(CObjectException & e)
		{
			kernelPrintDbg(DBG_ERR, "registerPageTreeObserver failed with cause="<<e.what());
		}
	}


	// consolidates page tree from newValue's indirect parent. If newValue is
	// CNull, uses oldValue's. This is correct because they both have been in
	// same intermediate node and both are direct values (change is in Kids
	// array). 
	IndiRef parentRef=(newType!=pNull)
		?newValue->getIndiRef()
		:oldValue->getIndiRef();
	shared_ptr<IProperty> parentProp_ptr=pdf->getIndirectProperty(parentRef);
	if(parentProp_ptr->getType()!=pDict)
	{
		// target of the parent reference is not dictionary,
		// this should not happen - some one is doing something nasty
		kernelPrintDbg(DBG_ERR, "newValue's parent is not dictionary. THIS SHOUL NOT HAPPEN");
		return;
	}

	// starts consolidation from parent interemdiate node
	shared_ptr<CDict> parentDict_ptr=IProperty::getSmartCObjectPtr<CDict>(parentProp_ptr);
	try
	{
		// if consolidatePageTree hasn't kept page count numbers, total number
		// of pages must be invalidated
		if(!pdf->consolidatePageTree(parentDict_ptr))
			pdf->pageCount=0;
	}catch(CObjectException & e)
	{
		kernelPrintDbg(DBG_ERR, "consolidatePageTree failed with cause="<<e.what());
	}

	// consolidates pageList 
	try
	{
		pdf->consolidatePageList(oldValue, newValue);
	}catch(CObjectException &e)
	{
		kernelPrintDbg(DBG_ERR, "consolidatePageList failed with cause="<<e.what());
	}
	
	kernelPrintDbg(DBG_DBG, "observer handler finished");
}

void CPdf::initRevisionSpecific()
{
using namespace utils;

	kernelPrintDbg(DBG_DBG, "");

	// Clean up part:
	// =============
	
	// cleans up indirect mapping
	if(indMap.size())
	{
		// checks for held values (smart pointer is not unique, so somebody
		// has to keep shared_ptr to same value)
		for(IndirectMapping::iterator i=indMap.begin(); i!=indMap.end(); i++)
		{
			IndiRef ref=i->first;
			shared_ptr<IProperty> value=i->second;
			if(!value.unique())
				kernelPrintDbg(DBG_WARN, "Somebody still holds property with with "<<ref);
		}
		kernelPrintDbg(DBG_INFO, "Cleaning up indirect mapping with "<<indMap.size()<<" elements");
		indMap.clear();
	}

	// cleans up and invalidates all returned pages
	if(pageList.size())
	{
		kernelPrintDbg(DBG_INFO, "Cleaning up pages list with "<<pageList.size()<<" elements");
		PageList::iterator i;
		for(i=pageList.begin(); i!=pageList.end(); i++)
		{
			kernelPrintDbg(DBG_DBG, "invalidating page at pos="<<i->first);
			// FIXME uncoment when method is reay
			//i->second->invalidate();
		}
		pageList.clear();
	}

	// invalidates pageCount
	pageCount=0;

	// invalidates document catalog and trailer
	// if someone holds reference (in shared_ptr assigned from them), prints
	// warning
	if((trailer.get()) && (!trailer.unique()))
		kernelPrintDbg(DBG_WARN, "Trailer dictionary is held by somebody.");
	trailer.reset();
	if((docCatalog.get()) && (!docCatalog.unique()))
		kernelPrintDbg(DBG_WARN, "Document catalog dictionary is held by somebody.");
	docCatalog.reset();
	
	// cleanup all returned outlines  -------------||----------------- 
	
	// Initialization part:
	// ===================
	
	// initialize trailer dictionary from xpdf trailer dictionary object
	// no free should be called because trailer is returned directly from XRef
	Object * trailerObj=xref->getTrailerDict();
	kernelPrintDbg(DBG_DBG, "Creating trailer dictionary from type="<<trailerObj->getType());
	trailer=boost::shared_ptr<CDict>(CDictFactory::getInstance(*trailerObj));
	
	// Intializes document catalog dictionary.
	// gets Root field from trailer, which should contain reference to catalog.
	// If no present or not reference, we have corrupted PDF file and exception
	// is thrown
	kernelPrintDbg(DBG_DBG, "Getting Root of page tree");
	IndiRef rootRef=utils::getRefFromDict("Root", trailer);
	shared_ptr<IProperty> prop_ptr=getIndirectProperty(rootRef);
	if(prop_ptr->getType()!=pDict)
	{
		kernelPrintDbg(DBG_CRIT, "Trailer dictionary doesn't point to correct document catalog.");
		throw ElementBadTypeException("Root");
	}
	kernelPrintDbg(DBG_INFO, "Document catalog successfully fetched");
	docCatalog=IProperty::getSmartCObjectPtr<CDict>(prop_ptr);
	
	// calls registerPageTreeObserver to page tree root - so it will be
	// registered to whole tree
	try
	{
		shared_ptr<IProperty> pageTreeProp_ptr=docCatalog->getProperty("Pages");
		if(pageTreeProp_ptr->getType()!=pRef)
		{
			kernelPrintDbg(DBG_ERR, "Pages field is not reference.");	
		}else
		{
			shared_ptr<CRef> pageTreeRoot_ptr=IProperty::getSmartCObjectPtr<CRef>(pageTreeProp_ptr);
			registerPageTreeObserver(pageTreeRoot_ptr, pageTreeWatchDog);
		}
	}catch(CObjectException & e)
	{
		kernelPrintDbg(DBG_WARN, "Document doesn't contain Page tree.");
	}
}

CPdf::CPdf(StreamWriter * stream, OpenMode openMode):pageTreeWatchDog(new PageTreeWatchDog(this)),change(false), modeController(NULL)
{
	// gets xref writer - if error occures, exception is thrown 
	xref=new XRefWriter(stream, this);
	mode=openMode;

	// initializes revision specific data for the newest revision
	initRevisionSpecific();

	// sets mode accoring openMode
	// ReadOnly and ReadWrite implies xref paranoid mode (default one) 
	// whereas Advanced mode sets easy mode because we want to have full 
	// control over document
	if(mode==Advanced)
		xref->setMode(XRefWriter::easy);
}

CPdf::~CPdf()
{
	kernelPrintDbg(DBG_DBG, "");

	// indirect mapping is cleaned up automaticaly
	
	// discards all returned pages
	for(PageList::iterator i=pageList.begin(); i!=pageList.end(); i++)
	{
		kernelPrintDbg(DBG_DBG, "Invalidating page at pos="<<i->first);
		// FIXME uncoment when method is ready
		//i->second->invalidate();
	}

	// TODO handle outlines when ready
	
	
	// deallocates XRefWriter
	delete xref;
}


//
// 
// this method can't be const because createObjFromXpdfObj requires 
// CPdf * not const CPdf * given by this
boost::shared_ptr<IProperty> CPdf::getIndirectProperty(IndiRef ref)
{
using namespace debug;

	kernelPrintDbg (DBG_DBG, ref);

	// find the key, if it exists
	IndirectMapping::iterator i = indMap.find(ref);
	if(i!=indMap.end())
	{
		// mapping exists, so returns value
		kernelPrintDbg(DBG_DBG, "mapping exists");
		return i->second;
	}

	kernelPrintDbg(DBG_DBG, "mapping doesn't exist")

	// mapping doesn't exist yet, so tries to create one
	// fetches object according reference
	Object obj;
	xref->fetch(ref.num, ref.gen, &obj);
	
	boost::shared_ptr<IProperty> prop_ptr;

	// creates cobject from value according type - indirect
	// parent is set to object reference (it is its own indirect parent)
	// created object is wrapped to smart pointer and if not pNull also added to
	// the mapping
	if(obj.getType()!=objNull)
	{
		IProperty * prop=utils::createObjFromXpdfObj(*this, obj, ref);
		prop_ptr=shared_ptr<IProperty>(prop);
		indMap.insert(IndirectMapping::value_type(ref, prop_ptr));
		kernelPrintDbg(DBG_INFO, "Mapping created for "<<ref);
	}else
	{
		kernelPrintDbg(DBG_INFO, ref<<" not available or points to objNull");
		prop_ptr=shared_ptr<CNull>(CNullFactory::getInstance());
	}

	obj.free ();
	return prop_ptr;
}


IndiRef CPdf::registerIndirectProperty(boost::shared_ptr<IProperty> ip, IndiRef ref)
{
using namespace debug;
using namespace utils;

	kernelPrintDbg(DBG_DBG, "");

	int state;
	if((state=xref->knowsRef(ref))!=RESERVED_REF)
		kernelPrintDbg(DBG_WARN, "Given reference is not in RESERVED_REF state. State is "<<state);
	
	// gets xpdf Object from given ip (which contain definitive value to
	// be stored), and registers change to XRefWriter (changeObject never 
	// throws in this context because this is first change of object - 
	// so no type check fails). We have to set this pdf temporarily, because
	// _makeXpdfObject function sets xref to created Object from ip->getPdf().
	// Finally restores original pdf value
	CPdf * original=ip->getPdf();
	ip->setPdf(this);
	::Object * obj=ip->_makeXpdfObject();
	ip->setPdf(original);
	kernelPrintDbg(DBG_DBG, "Initializating object with type="<<obj->getType()<<" to reserved reference "<<ref);
	xref->changeObject(ref.num, ref.gen, obj);

	// xpdf object has to be deallocated
	freeXpdfObject(obj);

	// creates return value from xpdf reference structure
	// and returns
	IndiRef reference(ref);
	kernelPrintDbg(DBG_INFO, "New indirect object inserted with reference "<<ref);
	change=true;
	return reference;
}

IndiRef CPdf::addProperty(boost::shared_ptr<IProperty> ip, IndiRef indiRef, ResolvedRefStorage & storage, bool followRefs )
{
	kernelPrintDbg(DBG_DBG, "");
	
	// checks whether given ip is from same pdf
	if(ip->getPdf()==this)
	{
		// ip is from same pdf and so all possible referencies are already in 
		// pdf too. We can clearly register with gien indiRef
		kernelPrintDbg(DBG_DBG, "Property from same pdf");
		return registerIndirectProperty(ip, indiRef);
	}

	// ip is not from same pdf - may be in different one or stand alone object
	// toSubstitute is deep copy of ip to prevent changes in original data.
	// Also sets same pdf as orignal to cloned to enable dereferencing
	shared_ptr<IProperty> toSubstitute=ip->clone();
	if(hasValidPdf(ip))
	{
		// locks cloned object to prevent making changes (kind of workaround)
		// we need indiref here because of mapping to new referencies and object
		// with valid pdf and indiref calls dispatchChange when something
		// changes
		toSubstitute->lockChange();
		toSubstitute->setPdf(ip->getPdf());
		toSubstitute->setIndiRef(ip->getIndiRef());
	}

	// toSubstitute may contain referencies deeper in hierarchy, so all
	// referencies have to be added or reserved to this pdf too before 
	// toSubstitute can be added itself
	subsReferencies(toSubstitute, storage, followRefs);

	// all possible referencies in toSubstitute are now added to this pdf and so
	// we can add toSubstitute. Reference is in storage mapping
	return registerIndirectProperty(toSubstitute, indiRef);
}

/** Reserves new referenece and creates mapping.
 * @param container Resolved mapping container.
 * @param xref XRefWriter for new reference reservation.
 * @param oldRef Original reference.
 *
 * Reserves new reference with XRefWriter::reserveRef method and if oldRef is
 * valid reference (checks with isValidRef method) also creates mapping [oldRef,
 * newRef to given container.
 *
 * @return newly reseved reference.
 */
IndiRef createMapping(ResolvedRefStorage & container, XRefWriter & xref, IndiRef oldRef)
{
using namespace debug;

	// this reference is processed for the first time. Reserves new
	// reference for indirect object and stores mapping from original
	// value to container.
	kernelPrintDbg(DBG_DBG, "processing "<<oldRef<<" for the first time");
	IndiRef indiRef(xref.reserveRef());
	
	// creates entry in container to enable reusing old reference to new
	// mapping is created only if oldRef is valid reference, which means that
	// object is indirect and if mapping is not in container yet
	if(isRefValid(&oldRef))
	{
		ResolvedRefStorage::iterator i;
		ResolvedRefStorage::value_type mapping(oldRef, indiRef);
		if(find(container.begin(), container.end(), mapping)==container.end())
		{
			container.push_back(mapping);
			kernelPrintDbg(DBG_DBG, "Created mapping from "<<oldRef<<" to "<<indiRef);
		}
	}

	// returns new reference.
	return indiRef;
}

IndiRef CPdf::subsReferencies(boost::shared_ptr<IProperty> ip, ResolvedRefStorage & container, bool followRefs)
{
using namespace utils;

	// TODO create constant
	IndiRef invalidRef;
	
	// this method makes sense only for properties from different pdf	
	assert(this!=ip->getPdf());
	
	kernelPrintDbg(debug::DBG_DBG,"property type="<<ip->getType()<<" container size="<<container.size());

	PropertyType type=ip->getType();
	ChildrenStorage childrenStorage;

	switch(type)
	{
		case pRef:
		{
			// checks if this reference has already been considered to prevent
			// endless loops for cyclic structures
			ResolvedRefStorage::iterator i;
			IndiRef ipRef=getValueFromSimple<CRef, pRef, IndiRef>(ip);
			for(i=container.begin(); i!=container.end(); i++)
			{
				IndiRef elem=i->first;
				if(elem==ipRef)
				{
					kernelPrintDbg(DBG_DBG, ipRef<<" already mapped to "<<elem);
					// this reference has already been processed, so reuses
					// reference which already has been created/reserved
					return elem;
				}
			}

			// reserves new reference and creates mapping
			IndiRef indiRef=createMapping(container, *xref, ipRef);

			// if followRefs is true, adds also target property too. Reference
			// is already registered yet and so registerIndirectProperty will
			// use it correctly
			if(followRefs)
			{
				kernelPrintDbg(DBG_DBG, "Following reference.");	
				// ip may be stand alone and in such case uses CNull
				shared_ptr<IProperty> followedIp;
				if(!hasValidPdf(ip))
					followedIp=shared_ptr<IProperty>(CNullFactory::getInstance());
				else
					// ip is from read pdf and so dereferences target value 					
					followedIp=ip->getPdf()->getIndirectProperty(ipRef);

				// adds dereferenced value using addProperty with collected
				// container. returned reference must be same as registered one 
				IndiRef addIndiRef=addProperty(followedIp, indiRef, container, followedIp);
				assert(addIndiRef==indiRef);
			}			
			return indiRef;
		}	
		// complex types (pArray, pDict and pStream) collects their children to the 
		// container
		case pArray:
			IProperty::getSmartCObjectPtr<CArray>(ip)->_getAllChildObjects(childrenStorage);
			break;
		case pDict:
			IProperty::getSmartCObjectPtr<CDict>(ip)->_getAllChildObjects(childrenStorage);
			break;
		case pStream:
			IProperty::getSmartCObjectPtr<CStream>(ip)->_getAllChildObjects(childrenStorage);
			break;

		// all other simple values are ok, nothing should return
		default:
			return invalidRef;
	}

	// goes throught all collected children and recursively calls this
	// method on each. If return value is non NULL, sets new child value to
	// returned reference.
	ChildrenStorage::iterator i;
	for(i=childrenStorage.begin(); i!=childrenStorage.end(); i++)
	{
		shared_ptr<IProperty> child=*i;
		if(!isRef(*child) && !isDict(*child) && !isArray(*child) && !isStream(*child))
		{
			// child is none of interesting type which may hold reference
			// inside, so skips such children
			continue;
		}
		
		IndiRef ref=subsReferencies(child, container, followRefs);
		if(isRefValid(&ref))
		{
			// new reference for this child
			boost::shared_ptr<CRef> ref_ptr=IProperty::getSmartCObjectPtr<CRef>(child);
			ref_ptr->setValue(ref);
			kernelPrintDbg(debug::DBG_DBG,"Reference changed to " << ref);
			continue;
		}
	}

	// also complex object is same - all referencies in this subtree are added
	// in this moment
	return invalidRef;
}

IndiRef CPdf::addIndirectProperty(boost::shared_ptr<IProperty> ip, bool followRefs)
{
using namespace utils;
using namespace debug;
using namespace boost;

	kernelPrintDbg(DBG_DBG, "");

	if(getMode()==ReadOnly)
	{
		kernelPrintDbg(DBG_ERR, "Document is in read-only mode now");
		throw ReadOnlyDocumentException("Document is in read-only mode.");
	}

	// reference can't be value of indirect property
	if(isRef(*ip))
	{
		kernelPrintDbg(DBG_ERR, "Reference can't be value of indirect property.");
		throw ElementBadTypeException("ip");
	}

	// creates empty resolvedStorage
	ResolvedRefStorage resolvedStorage;

	// resereves reference for new indirect object and if given ip is indirect
	// object too, creates also resolved mapping
	IndiRef indiRef=createMapping(resolvedStorage, *xref, ip->getIndiRef());

	// everything is checked now and all the work is delegated to recursive
	// addProperty method
	kernelPrintDbg(DBG_DBG, "Adding new indirect object.");
	IndiRef addRef=addProperty(ip, indiRef, resolvedStorage, followRefs);
	assert(addRef==indiRef);

	kernelPrintDbg(DBG_INFO, "New indirect object added with "<<indiRef<<" with type="<<ip->getType());

	return indiRef;
}

void CPdf::changeIndirectProperty(boost::shared_ptr<IProperty> prop)
{
	kernelPrintDbg(DBG_DBG, "");
	
	if(getMode()==ReadOnly)
	{
		kernelPrintDbg(DBG_ERR, "Document is in read-only mode now");
		throw ReadOnlyDocumentException("Document is in read-only mode.");
	}
	
	// checks property at first
	// it must be from same pdf
	if(prop->getPdf() != this)
	{
		kernelPrintDbg(DBG_ERR, "Given property is not from same pdf.");
		throw CObjInvalidObject();
	}
	// there must be mapping fro prop's indiref, but it doesn't have to be same
	// instance.
	IndiRef indiRef=prop->getIndiRef();
	if(indMap.find(indiRef)==indMap.end())
	{
		kernelPrintDbg(DBG_ERR, "Indirect mapping doesn't exist. prop seams to be fake.");
		throw CObjInvalidObject();
	}

	// gets xpdf Object instance and calls xref->change
	// changeObject may throw if we are in read only mode or if xrefwriter is
	// in paranoid mode and type check fails
	Object * propObject=prop->_makeXpdfObject();
	kernelPrintDbg(DBG_DBG, "Registering change to the XRefWriter");
	xref->changeObject(indiRef.num, indiRef.gen, propObject);
	utils::freeXpdfObject(propObject);

	// checks whether prop is same instance as one in mapping. If so, keeps
	// indirect mapping, because it has just changed some of its direct fields. 
	// Otherwise removes it, because new value is something totaly different. 
	// Mapping will be created in next getIndirectProperty call.
	if(prop==getIndirectProperty(indiRef))
	{
		kernelPrintDbg(DBG_INFO,  "Indirect mapping kept for "<<indiRef);
	}
	else
	{
		indMap.erase(indiRef);
		kernelPrintDbg(DBG_INFO, "Indirect mapping removed for "<<indiRef);
	}

	// sets change flag
	change=true;
}

CPdf * CPdf::getInstance(const char * filename, OpenMode mode)
{
using namespace std;

	kernelPrintDbg(debug::DBG_DBG, "");
	
	// openMode is read-only by default
	const char * openMode="r";
	
	// if mode is ReadWrite or higher, set to read-write mode starting at the 
	// begining.
	if(mode >= ReadWrite)
		openMode="r+";

	// opens file and creates (xpdf) FileStream
	FILE * file=fopen(filename, openMode);
	if(!file)
	{
		kernelPrintDbg(debug::DBG_ERR, "Unable to open file (reason="<<strerror(errno)<<")");
		throw PdfOpenException("Unable to open file.");
	}
	kernelPrintDbg(debug::DBG_DBG,"File \"" << filename << "\" open successfully in mode=" << openMode);
	
	// creates FileStream writer to enable changes to the File stream
	Object obj;
	obj.initNull();
	StreamWriter * stream=new FileStreamWriter(file, 0, gFalse, 0, &obj);
	kernelPrintDbg(debug::DBG_DBG,"File stream created");

	// stream is ready, creates CPdf instance
	try
	{
		CPdf * instance=new CPdf(stream, mode);
		kernelPrintDbg(debug::DBG_INFO, "Instance created successfully openMode=" << openMode);
		return instance;
	}catch(exception &e)
	{
		kernelPrintDbg(DBG_CRIT, "Pdf instance creation failed. cause="<<e.what());
		throw PdfOpenException("CPdf failed. reason=");
	}
}

int CPdf::close(bool saveFlag)
{
	kernelPrintDbg(debug::DBG_DBG, "");
	// saves if necessary
	if(saveFlag)
		save();
	
	// deletes this instance
	// all clean-up is made in destructor
	delete this;

	kernelPrintDbg(debug::DBG_INFO, "Instance deleted.")
	return 0;
}

boost::shared_ptr<CPage> CPdf::getPage(size_t pos)const
{
using namespace utils;

	kernelPrintDbg(DBG_DBG, "");

	if(pos < 1 || pos>getPageCount())
	{
		kernelPrintDbg(DBG_ERR, "Page out of range pos="<<pos);
		throw PageNotFoundException(pos);
	}

	// checks if page is available in pageList
	PageList::const_iterator i;
	if((i=pageList.find(pos))!=pageList.end())
	{
		kernelPrintDbg(DBG_INFO, "Page at pos="<<pos<<" found in pageList");
		return i->second;
	}

	// page is not available in pageList, searching has to be done
	// find throws an exception if any problem found, otherwise pageDict_ptr
	// contians Page dictionary at specified position.
	shared_ptr<CDict> rootPages_ptr=getPageTreeRoot(*this);
	if(!rootPages_ptr.get())
		throw PageNotFoundException(pos);
	shared_ptr<CDict> pageDict_ptr=findPageDict(*this, rootPages_ptr, 1, pos);

	// creates CPage instance from page dictionary and stores it to the pageList
	CPage * page=CPageFactory::getInstance(pageDict_ptr);
	shared_ptr<CPage> page_ptr(page);
	pageList.insert(PageList::value_type(pos, page_ptr));
	kernelPrintDbg(DBG_DBG, "New page added to the pageList size="<<pageList.size())

	return page_ptr;
}

unsigned int CPdf::getPageCount()const
{
using namespace utils;
	
	kernelPrintDbg(DBG_DBG, "");
	
	// try to use cached value - if zero, we have to get it from Page tree root
	if(pageCount)
	{
		kernelPrintDbg(DBG_DBG, "Uses cached value");
		kernelPrintDbg(DBG_INFO, "Page Count="<<pageCount);
		return pageCount;
	}
	
	shared_ptr<CDict> rootDict=getPageTreeRoot(*this);
	if(!rootDict.get())
		return 0;
	return pageCount=getKidsCount(rootDict);
}

boost::shared_ptr<CPage> CPdf::getNextPage(boost::shared_ptr<CPage> page)const
{
	kernelPrintDbg(DBG_DBG, "");

	size_t pos=getPagePosition(page);
	kernelPrintDbg(DBG_DBG, "Page position is "<<pos);
	pos++;
	
	// checks if we are in boundary after incrementation
	if(pos==0 || pos>getPageCount())
	{
		kernelPrintDbg(DBG_ERR, "Page is out of range pos="<<pos);
		throw PageNotFoundException(pos);
	}

	// page in range, uses getPage
	return getPage(pos);

}

boost::shared_ptr<CPage> CPdf::getPrevPage(boost::shared_ptr<CPage> page)const
{
	kernelPrintDbg(DBG_DBG, "");

	size_t pos=getPagePosition(page);
	kernelPrintDbg(DBG_DBG, "Page position is "<<pos);
	pos--;
	
	// checks if we are in boundary after incrementation
	if(pos==0 || pos>getPageCount())
	{
		kernelPrintDbg(DBG_ERR, "Page is out of range pos="<<pos);
		throw PageNotFoundException(pos);
	}

	// page in range, uses getPage
	return getPage(pos);
}

size_t CPdf::getPagePosition(boost::shared_ptr<CPage> page)const
{
	kernelPrintDbg(DBG_DBG, "");
		
	// search in returned page list
	PageList::iterator i;
	for(i=pageList.begin(); i!=pageList.end(); i++)
	{
		// compares page instances
		// This is ok even if they manage same page dictionary
		if(i->second == page)
		{
			kernelPrintDbg(DBG_INFO, "Page found at pos="<<i->first);
			return i->first;
		}
	}

	// page not found, it hasn't been returned by this pdf
	throw PageNotFoundException();
}


void CPdf::consolidatePageList(shared_ptr<IProperty> oldValue, shared_ptr<IProperty> newValue)
{
using namespace utils;

	kernelPrintDbg(DBG_DBG, "");

	// correction for all pages affected by this subtree change
	int difference=0;

	// position of first page which should be considered during consolidation 
	// because of value change
	size_t minPos=0;

	// handles original value - one before change
	// pNull means no previous value available (new sub tree has been added)
	kernelPrintDbg(DBG_DBG, "oldValue type="<<oldValue->getType());
	if(oldValue->getType()!=pNull)
	{
		// FIXME remove
		IndiRef oldValueRef=getValueFromSimple<CRef, pRef, IndiRef>(oldValue);
		
		// gets dictionary type - it has to be page or pages node
		shared_ptr<CDict> oldDict_ptr=getDictFromRef(oldValue);
		string oldDictType=getNameFromDict("Type", oldDict_ptr);

		// simple page is compared with all from pageList and if found, removes
		// it from list and invalidates it.
		// Difference is set to - 1, because one page is removed 
		if(oldDictType=="Page")
		{
			kernelPrintDbg(DBG_DBG, "oldValue was simple page dictionary");
			difference = -1;

			PageList::iterator i;
			for(i=pageList.begin(); i!=pageList.end(); i++)
			{
				// checks page's dictionary with old one
				if(i->second->getDictionary() == oldDict_ptr)
				{
					// FIXME: uncoment when method is ready
					//i->second->invalidate();
					size_t pos=i->first;
					minPos=pos;
					pageList.erase(i);
					kernelPrintDbg(DBG_INFO, "CPage(pos="<<pos<<") associated with oldValue page dictionary removed. pageList.size="<<pageList.size());
					break;
				}
			}
		}else
		{
			// Pages dictionary stands for intermediate node and so all CPages
			// from this sub tree are removed and invalidated
			// difference is set to -Count value (those number of pages are
			// removed)
			if(oldDictType=="Pages")
			{
				kernelPrintDbg(DBG_DBG, "oldValue was intermediate node dictionary.")
				difference = -getIntFromDict("Count", oldDict_ptr);

				// gets reference of oldValue - which is the root removed
				// subtree
				IndiRef ref=getValueFromSimple<CRef, pRef, IndiRef>(oldValue);
				
				PageList::iterator i;
				for(i=pageList.begin(); i!=pageList.end(); i++)
				{
					// checks page's dictionary whether it is in oldDict_ptr sub
					// tree and if so removes it from pageList
					if(isDescendant(*this, ref, i->second->getDictionary()))
					{
						// updates minPos with page position (if greater)
						size_t pos=i->first;
						if(pos > minPos)
							minPos=pos;
						
						// FIXME: uncoment when method is ready
						//i->second->invalidate();
						pageList.erase(i);
						kernelPrintDbg(DBG_INFO, "CPage(pos="<<pos<<") associated with oldValue page dictionary removed. pageList.size="<<pageList.size());

					}
				}
			}
		}
	}

	// oldValue subtree (if any) is consolidated now
	kernelPrintDbg(DBG_DBG, "All page dictionaries from oldValue subtree removed");

	// number of added pages by newValue tree
	int pagesCount=0;
	
	// handles new value - one after change
	// if pNull - no new value is available (subtree has been removed)
	kernelPrintDbg(DBG_DBG, "newValue type="<<newValue->getType());
	if(newValue->getType()!=pNull)
	{
		// gets dictionary type
		shared_ptr<CDict> newDict_ptr=getDictFromRef(newValue);
		string newDictType=getNameFromDict("Type", newDict_ptr);

		// page type adds only one page
		if(newDictType=="Page")
			pagesCount=1;

		// pages type adds Count pages
		if(newDictType=="Pages")
			pagesCount=getIntFromDict("Count", newDict_ptr);

		// try to get position of newValue node.  No pages from this sbtree can
		// be in the pageList, so we can set minPos to its position.
		// If getNodePosition throws, then this node is ambiguous and so we have
		// no information
		try
		{
			minPos = getNodePosition(*this, newValue);
		}catch(exception &e)
		{
			// position can't be determined
			// no special handling is needed, minPos keeps its value
		}

		kernelPrintDbg(DBG_DBG, "newValue sub tree has "<<pagesCount<<" page dictionaries");
	}

	// corrects difference with added pages
	difference += pagesCount;

	// no difference means no speacial handling for other pages
	// we have replaced old sub tree with new subtree with same number of pages
	if(difference==0)
		return;

	kernelPrintDbg(DBG_INFO, "pageList consolidation from minPos="<<minPos);
	
	// all pages with position greater than minPos, has to be consolidated
	PageList::iterator i;
	PageList readdContainer;
	for(i=pageList.begin(); i!=pageList.end(); i++)
	{
		size_t pos=i->first;
		shared_ptr<CPage> page=i->second;

		// all pages >= minPos are removed and readded with correct position
		if(pos >= minPos)
		{
			// collects all removed
			readdContainer.insert(PageList::value_type(pos, page));	
			pageList.erase(i);
		}
	}
	
	// checks minPos==0 and if so, we have to handle situation special way,
	// because don't have any information about previous position of oldValue
	// subtree. In such case all pages which should be readded are searched in
	// page tree and actual position is used.
	if(!minPos)
	{
		kernelPrintDbg(DBG_DBG,"Reassigning all pages positition.");
		for(i=readdContainer.begin(); i!=readdContainer.end(); i++)
		{
			// uses getNodePosition for each page's dictionary to find out
			// current position. If getNodePosition throws an exception, it
			// means that it can't be determined. Such page is invalidated.
			try
			{
				size_t pos=getNodePosition(*this, i->second->getDictionary());
				kernelPrintDbg(DBG_DBG, "Original position="<<i->first<<" new="<<pos);
				pageList.insert(PageList::value_type(pos, i->second));	
			}catch(exception & e)
			{
				kernelPrintDbg(DBG_WARN, "page with original position="<<i->first<<" is ambiguous. Invalidating.");
				// page position is ambiguous and so it has to be invalidate
				//TODO uncoment when method is ready
				//i->second->invalidate();
			}
		}
		return;
	}
	
	kernelPrintDbg(DBG_DBG, "Moving pages position with difference="<<difference<<" from page pos="<<minPos);
	// Information about page numbers which should be consolidated is available
	// so just adds difference for each in readdContainer
	// readds all removed with changed position (according difference)
	for(i=readdContainer.begin(); i!=readdContainer.end(); i++)
	{
		kernelPrintDbg(DBG_DBG, "Original position="<<i->first<<" new="<<i->first+difference);
		pageList.insert(PageList::value_type(i->first+difference, i->second));	
	}
	kernelPrintDbg(DBG_INFO, "pageList consolidation done.")
}


bool CPdf::consolidatePageTree(boost::shared_ptr<CDict> interNode)
{
using namespace utils;

	IndiRef interNodeRef=interNode->getIndiRef();
	kernelPrintDbg(DBG_DBG, "interNode "<<interNodeRef);

	// gets pdf of the node
	CPdf * pdf=interNode->getPdf();
	if(!pdf)
	{
		kernelPrintDbg(DBG_ERR, "internode has no pdf");
		return true;
	}
	
	// checks if interNode is real Pages dictionary
	string dictType=getNameFromDict("Type", interNode);
	if(dictType!="Pages")
	{
		kernelPrintDbg(DBG_ERR, "interNode is not correct intermediate node. type="<<dictType);
		throw ElementBadTypeException("InterNode");
	}

	shared_ptr<IProperty> kidsArrayProp_ptr=interNode->getProperty("Kids");
	if(kidsArrayProp_ptr->getType()!=pArray)
	{
		kernelPrintDbg(DBG_CRIT, "interNode's Kids field is not an array. type="<<kidsArrayProp_ptr->getType());
		// Kids field value must be aray
		throw ElementBadTypeException("Kids");
	}

	// following code should not throw an exception

	// gets all children from array
	shared_ptr<CArray> kidsArray_ptr=IProperty::getSmartCObjectPtr<CArray>(kidsArrayProp_ptr);
	vector<shared_ptr<IProperty> > kidsContainer;
	kidsArray_ptr->_getAllChildObjects(kidsContainer);

	// iterate through all array elements, dereference all of them and checks
	// dictionary type. 
	// Collects leaf page nodes from them (for Pages dict use Count value and
	// for Page it is obvious)
	size_t count=0;
	vector<shared_ptr<IProperty> >::iterator i;
	size_t index=0;
	for(i=kidsContainer.begin(); i!=kidsContainer.end(); i++, index++)
	{
		// each element should be reference
		if((*i)->getType()!=pRef)
		{
			// element is not reference, so we print warning and skip it
			// We are in Observer context so CAN'T remove element
			kernelPrintDbg(DBG_WARN, "Kids["<<index<<"] element must be reference. type="<<(*i)->getType());
			continue;
		}

		// we have reference so get indirect object. Indirect should be
		// dictionary. If it is not, we will print warning and skip this
		// element. We are in Observer context so CAN'T remove element
		IndiRef elementRef=getValueFromSimple<CRef, pRef, IndiRef>(*i);
		shared_ptr<IProperty> kidProp_ptr=pdf->getIndirectProperty(elementRef);
		if(kidProp_ptr->getType()!=pDict)
		{
			kernelPrintDbg(DBG_WARN, "Target of Kids["<<index<<"] is not dictionary. type="<<kidProp_ptr->getType());
			continue;
		}

		shared_ptr<CDict> kidDict_ptr=IProperty::getSmartCObjectPtr<CDict>(kidProp_ptr);
			
		// indirect dictionary should be Page or Pages
		// page dictionary increments count by 1 and if Pages, adds Count
		// if some problem occures, skips this element
		try
		{
			string dictType=getNameFromDict("Type", kidDict_ptr);
			if(dictType=="Page")
				count++;
			else
				if(dictType=="Pages")
					count+=getIntFromDict("Count", kidDict_ptr);
				else
				{
					kernelPrintDbg(DBG_WARN, " interNode contains reference to dictionary with bad type="<<dictType);
					// bad dictionaty type is skipped
					continue;
				}
		}catch(CObjectException & e)
		{
			kernelPrintDbg(DBG_WARN, "Problem with dictionary. cause="<<e.what());
			continue;
		}

		// We have page or pages node at this moment. Checks Parent field
		// whether it is reference and points to interNode. All errors are
		// corrected.
		try
		{
			IndiRef parentRef;
			parentRef=getRefFromDict("Parent", kidDict_ptr);
			if(! (parentRef==interNode->getIndiRef()))
			{
				kernelPrintDbg(DBG_WARN, "Kids["<<index<<"] element dictionary doesn't have Parent with proper reference. Correcting to "<<parentRef);
				CRef cref(interNode->getIndiRef());
				kidDict_ptr->setProperty("Parent", cref);
			}
			
		}catch(ElementNotFoundException & e)
		{
			// Parent not found at all
			// field is added
			IndiRef parentRef=interNode->getIndiRef();
			kernelPrintDbg(DBG_WARN, "No Parent field found. Correcting to "<<parentRef);
			CRef cref(parentRef);
			kidDict_ptr->addProperty("Parent", cref);
		}catch(ElementBadTypeException & e)
		{
			// Parent is found but with bad type
			// Parent field is removed in first step and than added with correct
			// this is because of different type of field value which may lead
			// to exception if types are checked (in paranoid mode of
			// XRefWriter)
			IndiRef parentRef=interNode->getIndiRef();
			kernelPrintDbg(DBG_WARN, "Parent field found but with bad type. Correcting to "<<parentRef);
			kidDict_ptr->delProperty("Parent");
			CRef cref(parentRef);
			kidDict_ptr->addProperty("Parent", cref);
		}

	}

	// count is collected for this node, checks if it matches actual value and 
	// if not sets new value and distribute it to all parents. Parent can throw
	// but this node and its sub tree is ok now
	try
	{
		size_t currentCount=getIntFromDict("Count", interNode);
		if(currentCount == count)
		{
			// count field is ok - no parent consolidation has to be done
			kernelPrintDbg(DBG_DBG, "No need to for further consolidation Count field is ok");
			return true;
		}
	}catch(CObjectException &e)
	{
		// not found or bad type
		// no special handling - just continues as if no bad Count value was
		// present - This should never happen
		kernelPrintDbg(DBG_WARN, "Intermediate node without or with bad typed Count field.");
	}

	// Count field is not correct, sets new value and invalidates pagesCount
	kernelPrintDbg(DBG_WARN, "Count field is not correct. Reconstructing correct value.");
	CInt countProp(count);
	kernelPrintDbg(DBG_INFO, "new interNode Count="<<count);
	interNode->setProperty("Count", countProp);
	
	// distribute value also to fathers - if any
	try
	{
		// TODO be carefull top level parent may be parent of himself
		shared_ptr<IProperty> parentRef_ptr=interNode->getProperty("Parent");
		shared_ptr<CDict> parentDict_ptr=getDictFromRef(parentRef_ptr);

		// calls recursively
		kernelPrintDbg(DBG_DBG, "Distributing count value to parent");
		consolidatePageTree(parentDict_ptr);
	}
	catch(exception &e)
	{
		// no parent in intermediate node means root of page tree
		// also consolidatePageTree can throw, but we don't handle it from here.
		// It may be serious problem with demaged tree and so reconstruction has
		// to be done by hand
	}

	// consolidation had to be done
	kernelPrintDbg(DBG_INFO, "pageTree consolidation done for inter node "<<interNodeRef);
	return false;
}

boost::shared_ptr<CPage> CPdf::insertPage(boost::shared_ptr<CPage> page, size_t pos)
{
using namespace utils;

	kernelPrintDbg(DBG_DBG, "pos="<<pos);

	if(getMode()==ReadOnly)
	{
		kernelPrintDbg(DBG_ERR, "Document is in read-only mode now");
		throw ReadOnlyDocumentException("Document is in read-only mode.");
	}
		
	// zero position is corrected to 1
	if(pos==0)
		pos=1;

	// gets intermediate node which includes node at given position. To enable
	// also to insert after last page, following work around is done:
	// if page is greater than page count, append flag is set to true and so new
	// dictionary is stored after last position (instead of storePostion).
	size_t count=getPageCount();
	size_t storePostion=pos;
	bool append=false;
	if(pos>count)
	{
		// sets that we are appending and sets storePostion to last position
		append=true;
		storePostion=count;
		kernelPrintDbg(DBG_INFO, "inserting after (new last page) position="<<storePostion);
	}

	// gets intermediate node where to insert new page
	// in degenerated case, when there are no pages in the tree, we have to
	// handle it special way
	shared_ptr<CDict> interNode_ptr;
	shared_ptr<CRef> currRef;
	// by default it is root of page tree
	interNode_ptr=getPageTreeRoot(*this);
	if(!interNode_ptr.get())
	{
		// Root of page dictionary doesn't exist
		// TODO handle
	}
	if(count)
	{
		// stores new page at position of existing page
		
		// searches for page at storePosition and gets its reference
		// page dictionary has to be an indirect object, so getIndiRef returns
		// dictionary reference
		shared_ptr<CDict> currentPage_ptr=findPageDict(*this, interNode_ptr, 1, storePostion);
		currRef=shared_ptr<CRef>(CRefFactory::getInstance(currentPage_ptr->getIndiRef()));
		
		// gets parent of found dictionary which maintains 
		shared_ptr<IProperty> parentRef_ptr=currentPage_ptr->getProperty("Parent");
		interNode_ptr=getDictFromRef(parentRef_ptr);
	}

	// gets Kids array where to insert new page dictionary
	shared_ptr<IProperty> kidsProp_ptr=interNode_ptr->getProperty("Kids");
	if(kidsProp_ptr->getType()!=pArray)
	{
		kernelPrintDbg(DBG_CRIT, "Pages Kids field is not an array type="<<kidsProp_ptr->getType());
		// Kids is not array - malformed intermediate node
		throw MalformedFormatExeption("Intermediate node Kids field is not an array.");
	}
	shared_ptr<CArray> kids_ptr=IProperty::getSmartCObjectPtr<CArray>(kidsProp_ptr);
	
	// gets index in Kids array where to store.
	// by default insert at 1st position (index is 0)
	size_t kidsIndex=0;
	if(count)
	{
		// gets index of searched node's reference in Kids array - if position 
		// can't be determined unambiguously (getPropertyId returns more positions), 
		// throws exception
		vector<CArray::PropertyId> positions;
		getPropertyId<CArray, vector<CArray::PropertyId> >(kids_ptr, currRef, positions);
		if(positions.size()>1)
		{
			kernelPrintDbg(DBG_ERR, "Page can't be created, because page tree is ambiguous for node at pos="<<storePostion);
			throw AmbiguousPageTreeException();
		}
		kidsIndex=positions[0]+append;
	}

	// Now it is safe to add indirect object, because there is nothing that can
	// fail
	shared_ptr<CDict> pageDict=page->getDictionary();
	if(pageDict->getPdf() && pageDict->getPdf()!=this)
	{
		// page comes from different valid pdf - we have to create clone and
		// remove Parent field from it. Also inheritable properties have to be
		// handled
		CPdf * pageDictPdf=pageDict->getPdf();
		IndiRef pageDictIndiRef=pageDict->getIndiRef();
		pageDict=IProperty::getSmartCObjectPtr<CDict>(pageDict->clone());
		pageDict->delProperty("Parent");

		// clone needs to set pdf and indirect, because these values are not
		// cloned and they are needed for indirect properties dereferencing
		// (pdf) and for internal referencies (some of pageDict members may
		// refer to page). This implies that pageDict has to be locked for
		// dispatchChange.
		pageDict->lockChange();
		pageDict->setPdf(pageDictPdf);
		pageDict->setIndiRef(pageDictIndiRef);
		setInheritablePageAttr(pageDict);
	}
	
	// adds pageDict as new indirect property (also with properties referenced 
	// by this dictionary.
	// All page dictionaries must be indirect objects and addIndirectProperty
	// method also solves problems with deep copy and page from different file
	// transition
	IndiRef pageRef=addIndirectProperty(pageDict, true);

	// adds newly created page dictionary to the kids array at kidsIndex
	// position. This triggers pageTreeWatchDog for consolidation and observer
	// is registered also on newly added reference
	CRef pageCRef(pageRef);
	kids_ptr->addProperty(kidsIndex, pageCRef);
	
	// page dictionary is stored in the tree, consolidation is also done at this
	// moment
	// CPage can be created and inserted to the pageList
	shared_ptr<CDict> newPageDict_ptr=IProperty::getSmartCObjectPtr<CDict>(getIndirectProperty(pageRef));
	shared_ptr<CPage> newPage_ptr(CPageFactory::getInstance(newPageDict_ptr));
	pageList.insert(PageList::value_type(storePostion, newPage_ptr));
	kernelPrintDbg(DBG_DBG, "New page added to the pageList size="<<pageList.size())
	return newPage_ptr;
}

void CPdf::removePage(size_t pos)
{
using namespace utils;

	kernelPrintDbg(DBG_DBG, "");

	if(getMode()==ReadOnly)
	{
		kernelPrintDbg(DBG_ERR, "Document is in read-only mode now");
		throw ReadOnlyDocumentException("Document is in read-only mode.");
	}

	// checks position
	if(1>pos || pos>getPageCount())
		throw PageNotFoundException(pos);

	// Searches for page dictionary at given pos and gets its reference.
	// getPageTreeRoot doesn't fail, because we are in page range and so it has
	// to exist
	shared_ptr<CDict> rootDict=getPageTreeRoot(*this);
	shared_ptr<CDict> currentPage_ptr=findPageDict(*this, rootDict, 1, pos);
	shared_ptr<CRef> currRef(CRefFactory::getInstance(currentPage_ptr->getIndiRef()));
	
	// Gets parent field from found page dictionary and gets its Kids array
	// TODO this may be problem - because there may be only one page in
	// document which could have no parent - same as in insertPage
	shared_ptr<IProperty> parentRef_ptr=currentPage_ptr->getProperty("Parent");
	shared_ptr<CDict> interNode_ptr=getDictFromRef(parentRef_ptr);
	shared_ptr<IProperty> kidsProp_ptr=interNode_ptr->getProperty("Kids");
	if(kidsProp_ptr->getType()!=pArray)
	{
		kernelPrintDbg(DBG_CRIT, "Pages Kids field is not an array type="<<kidsProp_ptr->getType());
		// Kids is not array - malformed intermediate node
		throw MalformedFormatExeption("Intermediate node Kids field is not an array.");
	}
	shared_ptr<CArray> kids_ptr=IProperty::getSmartCObjectPtr<CArray>(kidsProp_ptr);

	// gets index of searched node in Kids array and removes element from found
	// position - if position can't be determined unambiguously (getPropertyId
	// returns more positions), exception is thrown
	IndiRef tmpRef=currentPage_ptr->getIndiRef();
	vector<CArray::PropertyId> positions;
	getPropertyId<CArray, vector<CArray::PropertyId> >(kids_ptr, currRef, positions);
	if(positions.size()>1)
	{
		kernelPrintDbg(DBG_ERR, "Page can't be created, because page tree is ambiguous for node at pos="<<pos);
		throw AmbiguousPageTreeException();
	}
	
	// removing triggers pageTreeWatchDog consolidation
	size_t kidsIndex=positions[0];
	kids_ptr->delProperty(kidsIndex);
	
	// page dictionary is removed from the tree, consolidation is done also for
	// pageList at this moment
}

void CPdf::save(bool newRevision)const
{
	kernelPrintDbg(DBG_DBG, "");

	if(getMode()==ReadOnly)
	{
		kernelPrintDbg(DBG_ERR, "Document is in read-only mode now");
		throw ReadOnlyDocumentException("Document is in read-only mode.");
	}
	
	// checks actual revision
	if(xref->getActualRevision())
	{
		kernelPrintDbg(DBG_ERR, "Document is not in latest revision");
		throw ReadOnlyDocumentException("Document is in read-only mode.");
	}
	
	// we are in the newest revision, so changes can be saved
	// delegates all work to the XRefWriter and set change to 
	// mark, that no changes were stored
	xref->saveChanges(newRevision);
	change=false;
}

void CPdf::clone(FILE * file)const
{
using namespace debug;

	kernelPrintDbg(DBG_DBG, "");

	if(!file)
	{
		kernelPrintDbg(DBG_ERR, "output file is NULL");
		return;
	}
	
	// delagates to XRefWriter
	xref->cloneRevision(file);
}

void CPdf::changeRevision(revision_t revisionNum)
{
	kernelPrintDbg(DBG_DBG, "");
	
	// set revision xref->changeRevision
	xref->changeRevision(revisionNum);
	
	// prepares internal structures for new revision
	initRevisionSpecific();
}

} // end of pdfobjects namespace
