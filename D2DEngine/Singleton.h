#pragma once

template <typename T>
class Singleton
{
protected:


public:
	Singleton()
	{
		assert(s_instance == nullptr && "Singleton instance aleady created!");
		s_instance = static_cast<T*>(this);
	}

	~Singleton() = default;

	static void Create()
	{
		if (!s_instance)
			s_instance = new T();
	}

	static T& GetInstance()
	{
		if (!s_instance)
			s_instance = new T();
		return *s_instance;
	}
	
	static void Destroy()
	{
		delete s_instance;
		s_instance = nullptr;
	}

private:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	static T* s_instance;
};

template <typename T>
T* Singleton<T>::s_instance = nullptr;