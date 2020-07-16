/*
 * browserSupport.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */

#include "browserSupport.h"

#include <string>

url::url(const std::string& urlText)
	: urlText(urlText), urlValid(true)
{	
}

url::url()
	: urlText(),urlValid(false)
{
}
url::~url() {

}
void url::text(const std::string& urlText) {
	this->urlText = urlText;
}
std::string url::text() const {
	return urlText;
}
bool url::valid() const {
	return urlValid;
}
bool url::operator< (const url& rhs) const {
	return urlText < rhs.urlText;
}
bool url::operator==(const url& rhs) const {
	return urlText == rhs.urlText;
}

url::operator std::string() const
{
	return text();
}

std::ostream& operator<<(std::ostream& out, const url& other) {

	out << other.text() << std::endl;

	return out;
}

browserSupport::browserSupport() 
	: size(50), currentUrl()
{

}
browserSupport::~browserSupport() {

}
url browserSupport::back() {
	if (!backUrl.empty()) {
		if (currentUrl.valid()) {
			forwUrl.push(currentUrl);
		}
		currentUrl = backUrl.top();
		backUrl.pop();
	}
	return currentUrl;
}
url browserSupport::forward() {
	if (!forwUrl.empty()) {
		if (currentUrl.valid()) {
			backUrl.push(currentUrl);
		}
		currentUrl = forwUrl.top();
		forwUrl.pop();
	}
	return currentUrl;
}
void browserSupport::display(const url& newURL) {
	if (currentUrl.valid()) {
		backUrl.push(currentUrl);
	}

	currentUrl = newURL;
	if (historyQueue.empty()) {
		historyQueue.push(currentUrl);
	}
	else if (!historyQueue.empty() && currentUrl != historyQueue.back()) {
		historyQueue.push(currentUrl);
	}
	if(historyQueue.size() > maximum()) {
		historyQueue.pop();
	}

}
std::size_t browserSupport::clearHistory() {
	std::size_t total = historyQueue.size();
	historyQueue.clear();
	return total;
}
std::size_t browserSupport::clearCache() {
	std::size_t total = 0;
	if (backUrl.size() > size) {
		total += size;
	}
	else if (backUrl.size() < size) {
		total += backUrl.size();
	}
	if (forwUrl.size() > size) {
		total += size;
	}
	else if (forwUrl.size() < size) {
		total += forwUrl.size();
	}
	else if(backUrl.size() == size && forwUrl.size() == size){
		total += forwUrl.size()/2;
		total += backUrl.size()/2;
	}
	if (currentUrl.valid()) {
		total += 1;		
	}
	
	backUrl.clear();
	forwUrl.clear();
	currentUrl.text("");
	return total;

}
std::size_t browserSupport::maximum() const {
	return size;
}
void browserSupport::maximum(std::size_t newMax) {
	
	if (newMax < historyQueue.size()) {
		
		std::size_t diff = historyQueue.size() - newMax;
		while (diff > 0) {
			historyQueue.pop();
			diff--;
		}
	}
	size = newMax;
}

std::size_t browserSupport::history(std::vector<url> &historyURLs)
{
	historyURLs.clear();
	browserSupport::pVector = &historyURLs;

	historyQueue.traverse(&browserSupport::buildHistory);


	browserSupport::pVector = nullptr;

	return 0;
}

std::vector<url>* browserSupport::pVector = nullptr;

void browserSupport::buildHistory(const url& nextURL)
{
	if (pVector != nullptr)
	{
		(*pVector).push_back(nextURL);
	}
}
