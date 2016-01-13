#include <collage.h>

namespace cs225
{
	collage::collage(uint64_t size)
	:dinoray{size}, xray{size}, yray{size}
	{
		for(uint64_t i=0; i<size; i++)
			dinoray[i] = NULL;
	}
	
	collage::collage(const collage &other)
	:dinoray{other.dinoray.size()}, xray{other.xray.size()}, yray{other.yray.size()}
	{
		for(uint64_t i=0; i<dinoray.size(); i++){
			if(!other.dinoray[i].empty()){
				dinoray[i] = new epng::png(*other.dinoray[i]);
				xray[i] = other.xray[i];
				yray[i] = other.yray[i];
			}
		}
	}
	
	collage::collage(collage &&other)
	:dinoray{}, xray{}, yray{}
	{
		swap(other);
	}
	
	collage& collage::operator=(collage rhs)
	{
		swap(rhs);
		return *this;
	}
	
	collage::~collage()
	{
		clear();
	}
	
	void collage::clear()
	{
		dinoray.clear();
		xray.clear();
		yray.clear();
	}
	
	void collage::swap(collage &other)
	{
		dinoray.swap(other.dinoray);			//might fuck up
		xray.swap(other.xray);
		yray.swap(other.yray);
	}
	
	void collage::layers(uint64_t max)
	{
		dinoray.resize(max);
		xray.resize(max);
		yray.resize(max);
	}
	
	uint64_t collage::layers() const
	{
		return dinoray.size();
	}
	
	uint64_t collage::filled() const
	{
		uint64_t x=0;
		for(uint64_t i=0; i<dinoray.size(); i++){
			if(!dinoray[i].empty())
				x++;
		}
		return x;
	}
	
	void collage::emplace_picture(const std::string& filename, uint64_t index, uint64_t x, uint64_t y)
	{
		if(index >= dinoray.size())
			throw std::out_of_range("invalid index");
		if(dinoray[index].empty())
			dinoray[index] = new epng::png(filename);
		else
			dinoray[index]->load(filename);
		xray[index] = x;
		yray[index] = y;
	}
	
	void collage::change_layer(uint64_t src, uint64_t dest)
	{
		if(dest >= dinoray.size() || src >= dinoray.size())
			throw std::out_of_range("invalid index");
		dinoray[dest].clear();
		dinoray[dest].swap(dinoray[src]);
		xray[dest] = xray[src];
		yray[dest] = yray[src];
	}
	
	void collage::position(uint64_t index, uint64_t x, uint64_t y)
	{
		if(index >= dinoray.size())
			throw std::out_of_range("invalid index");
		if(dinoray[index].empty())
			throw std::invalid_argument("no image");
		xray[index] = x;
		yray[index] = y;
	}
	
	void collage::erase(uint64_t index)
	{
		if(index >= dinoray.size())
			throw std::out_of_range("invalid index");
		dinoray[index].clear();
	}
	
	const epng::png* collage::at(uint64_t index) const
	{
		if(index >= dinoray.size())
			throw std::out_of_range("invalid index");
		return &(*dinoray[index]);
	}
	
	epng::png* collage::at(uint64_t index)
	{
		if(index >= dinoray.size())
			throw std::out_of_range("invalid index");
		return &(*dinoray[index]);
	}
	
	epng::png collage::draw() const
	{
		scoped_ptr<epng::png> coll{new epng::png{}};
		for(uint64_t i=0; i<dinoray.size(); i++){
			if(!dinoray[i].empty()){
				if(coll->width() < dinoray[i]->width()+xray[i])
					coll->resize(dinoray[i]->width()+xray[i], coll->height());
				if(coll->height() < dinoray[i]->height()+yray[i])
					coll->resize(coll->width(), dinoray[i]->height()+yray[i]);
				for(size_t j=0; j<dinoray[i]->width(); j++){
					for(size_t k=0; k<dinoray[i]->height(); k++){
						(*coll)(j+xray[i], k+yray[i])->red = (*dinoray[i])(j, k)->red;
						(*coll)(j+xray[i], k+yray[i])->green = (*dinoray[i])(j, k)->green;
						(*coll)(j+xray[i], k+yray[i])->blue = (*dinoray[i])(j, k)->blue;
						(*coll)(j+xray[i], k+yray[i])->alpha = (*dinoray[i])(j, k)->alpha;
					}
				}
			}
		}
		return *coll;
	}
}	
