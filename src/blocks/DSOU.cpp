#include "DSOU.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "LECF.hpp"
#include "LFLF.hpp"

DSOU::DSOU(Game *game, LECF *lecf)
{
	_ids.push_back(0);
	_offsets.push_back(0);

	for (int i = 0; i < lecf->getNumberOfLFLFs(); i++)
		for (int j = 0; j < lecf->getLFLF(i)->getNumberOfSOUNOffsets(); j++)
		{
			_ids.push_back(game->getRoom(i)->getID());
			_offsets.push_back(lecf->getLFLF(i)->getSOUNOffset(j));
		}

	_nItems = _ids.size();
}

uint32_t DSOU::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nItems
	size += _ids.size() * sizeof(uint8_t); // ids
	size += _offsets.size() * sizeof(uint32_t); // offsets
	return size;
}

void DSOU::write(fstream &f)
{
	IO::writeString(f, "DSOU");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DSOU::~DSOU()
{
}

