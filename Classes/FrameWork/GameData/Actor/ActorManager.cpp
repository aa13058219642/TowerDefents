#include "ActorManager.h"

ActorManager* ActorManager::p_myinstance = nullptr;

ActorManager::ActorManager()
{

}

ActorManager::~ActorManager()
{
}

ActorManager* ActorManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new ActorManager();
	}
	return p_myinstance;
}

void ActorManager::init(Layer* layer)
{
	m_layer = layer;
}

void ActorManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void ActorManager::LoadResource(const vector<Name>& resNameList)
{

	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/Actor.json");
	CCASSERT(!data.isNull(), "[Actor.json] Lost!");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("actordata"), "illegal [Actor.json]");

	//3.读取json数据
	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int Size = root["actordata"].Size();
	for (int i = 0; i < Size; i++) {
		string name = root["actordata"][i]["name"].GetString();
		if (fullLoad || std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			ActorData d;
			d.defaultanimate=root["actordata"][i]["defaultanimate"].GetString();
			int size = root["actordata"][i]["actioncount"].GetInt();
			CCASSERT(size != 0, "framecount must NOT equal 0");
			for (int j = 0; j < size; j++) {
				d.maps[root["actordata"][i]["actionName"][j].GetString()] = root["actordata"][i]["animateName"][j].GetString();
			}
			m_actordata[name] = d;
		}
	}
}

void ActorManager::FreeAllResource()
{
	//for (auto var : m_actorlist)
	//	delete var.second;
	//m_actorlist.clear();
	m_actordata.clear();
}

void ActorManager::FreeResource(const vector<Name>& resName)
{
	for (auto name : resName)
	{
		if (m_actordata.find(name) != m_actordata.end())
		{
			//delete m_effectlist[name];
			m_actordata.erase(name);
		}
	}
}

Actor* ActorManager::createActor(int id, Name name)
{
	if (m_actordata.find(name) != m_actordata.end())
	{
		if (m_actorlist.find(id) != m_actorlist.end())
		{
			destoryActor(id);
		}
		Actor* actor = new Actor(id, m_actordata[name], m_layer);
		m_actorlist[id] = actor;
		return actor;
	}
	CCASSERT(false, "can NOT create actor");
	return nullptr;
}

void ActorManager::playAction(int id, Name actionName, float playtime)
{
	m_actorlist[id]->playAction(actionName, playtime);
}

void ActorManager::removeActor(int id)
{
	m_actorlist[id]->remove();
}

void ActorManager::destoryActor(int id)
{
	delete m_actorlist[id];
	m_actorlist.erase(id);
}
















