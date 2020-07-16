/*
 * browserSupport.h
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */

#ifndef BROWSERSUPPORT_H_
#define BROWSERSUPPORT_H_

#include <string>
#include <vector>

#include "stack.h"
#include "queue.h"

class url
{
	private:
		std::string urlText;
		bool urlValid;
	public:
	   // you need to implement these
		url(const std::string &urlText);
		url();
		virtual ~url();
		void text(const std::string &urlText);
		std::string text() const;
		bool valid() const;
		bool operator< (const url& rhs) const;
		bool operator==(const url& rhs) const;

      // these are implemented for you
      operator std::string() const; // this allow us to do the following:
      //  url myURL("utdallas.edu");
      //  std::string text = static_cast<std::string>(myURL);
		bool operator> (const url& rhs) const { return rhs < *this; }
		bool operator<=(const url& rhs) const { return !(*this > rhs); }
		bool operator>=(const url& rhs) const { return !(*this < rhs); }
		bool operator!=(const url& rhs) const { return !(*this == rhs); }
};

// you need to implement this
std::ostream& operator<<(std::ostream &out, const url &other);

class browserSupport
{
	private:
      // this is needed for displaying the histroy
		static std::vector<url> *pVector;
		queue<url> historyQueue;
		stack<url> backUrl;
		stack<url> forwUrl;
		std::size_t size;
		url currentUrl;

	public:
	   // you need to implement these
		browserSupport();
		virtual ~browserSupport();
		url back();
		url forward();
		void display(const url &newURL);
		std::size_t clearHistory();
		std::size_t clearCache();
		std::size_t maximum() const;
		void maximum(std::size_t newMax);
		
		// this is implemented for you
		std::size_t history(std::vector<url> &historyURLs);
	private:
	   // this is implemented for you
		static void buildHistory(const url &nextURL);
};

#endif /* BROWSERSUPPORT_H_ */
