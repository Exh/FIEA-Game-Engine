/**	@class Attributed
*	@brief Definition of glue class Attributed
*/
#pragma once
#include "Scope.h"

namespace Library
{
	/**	@class Attributed
	*	@brief Glue class that binds scopes to native classes
	*/
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:
		/**	@brief Default Constructor that initialises the class members */
		Attributed();

		/**	@brief virtual destructor that frees memory used by its members */
		virtual ~Attributed() = default;

		/**	@brief Copyconstructor to deep copy one attribute into another
		*	@param the attributed class to copy from
		*/
		Attributed(const Attributed& rhs);
		
		/**	@brief Overloaded = operator to deep copy one attribute into another
		*	@param the attributed class to copy from
		*	@return reference to the copied attributed class
		*/
		Attributed& operator=(const Attributed& rhs);

		/**	@brief Populate the class with the prescribed members
		*/
		void Populate();

		/**	@brief Returns if the attribute is a prescribed attribute
		*	@param The attribute to check for
		*	@return true, if the attribute is a prescribed attribute, false otherwise
		*/
		bool IsPrescribedAttribute(const std::string& attributeName) const;

		/**	@brief Returns if the attribute is an Auxiliary attribute
		*	@param the attribute to check for
		*	@return true, if the attribute is an Auxiliary attribute, false otherwise
		*/
		bool IsAuxiliaryAttribute(const std::string& attributeName) const;

		/**	@brief returns if the attribute is an attribute (prescribed or Auxiliary)
		*	@param the attribute to check
		*	@return true, if it is an attribute, false otherwise
		*/
		bool IsAttribute(const std::string& attributeName) const;

		/**	@brief Provides a wrapper for Scope's Append
		*	@param the attribute to add into the scope
		*	@return reference to the appended datum or an existing one, if one with the same name exists
		*	@throws std::exception, if it is a prescribed attribute or if trying to modify 'this'
		*/
		Datum& AppendAuxiliaryAttribute(const std::string& attributeName);

		/**	@brief Returns the index of the first auxiliary attribute
		*	@return auxillary attribute start index
		*/
		std::uint32_t AuxiliaryBegin() const;

		/**	@brief Compares two attributed classes for equality, ignoring the "this" attribute
		*	@param the class to compare to
		*	@return true, if the two classes are the same, false otherwise
		*/
		bool operator==(const Attributed& rhs) const;

		/**	@brief Compares two attributed classes for inequality, ignoring the "this" attribute
		*	@param the class to compare to
		*	@return true, if the two classes are not the same, false if they are
		*/
		bool operator!=(const Attributed& rhs) const;

		/**	@brief Clears all the attributes of the class except the 'this' attribute
		*/	
		void Clear();
		
		/**	@brief Copies all the auxillary attributes from the rhs
		*	@param the attributed from which to copy all the auxillary attributes
		*/
		void CopyAuxillaryAttributes(const Attributed& rhs);

	protected:
		/**	@class Signature
		*	@brief Protected inner class to store the signature of an attribute. It is used as a value object to populate the signatures hashmap
		*/
		class Signature
		{
			friend class Attributed;
		public:
			/**	@brief Default constructor to set default values to members	*/
			Signature();

			/**	@brief Default destructor */
			~Signature() = default;

			/**	@brief Constructor to set passed in values to members */
			Signature(const std::string& name, Datum::DatumType type, void* initialValue,std::uint32_t size,void* storage);
		private:
			std::string Name;
			Datum::DatumType Type; 
			void* InitialValue; ///< nullptr if its external
			std::uint32_t DataSize;
			void* Storage; ///< nullptr if its internal
		};

	private:
		/* Method to retrieve signature at the index from the hashmap */
		Signature& GetSignature(std::uint32_t index);

	public:
		//static HashMap<std::uint32_t, Vector<Signature>> sSignatures; ///< Stores the signatures for each class type
		Vector<Signature> mSignatures;

		/* Macros to facilitate setting up and adding signatures to the hashmap */
//#define INIT_SIGNATURES	\
//if (sSignatures.ContainsKey(TypeIdInstance()))\
//{\
//	std::uint32_t size = sSignatures[TypeIdInstance()].Size();\
//	sSignatures[TypeIdInstance()].Clear();\
//	sSignatures[TypeIdInstance()].Reserve(size);\
//}

#define INIT_SIGNATURES	\
	std::uint32_t size = mSignatures.Size();\
	mSignatures.Clear();\
	mSignatures.Reserve(size);\

#define INTERNAL_ATTRIBUTE(name, type, value, size) \
	mSignatures.PushBack(Signature(std::string(name),type,value,size,nullptr));

	//sSignatures[TypeIdInstance()].PushBack(Signature(std::string(name),type,value,size,nullptr));
#define EXTERNAL_ATTRIBUTE(name, type, value, size)	\
	mSignatures.PushBack(Signature(std::string(name),type,nullptr,size,value));

	//sSignatures[TypeIdInstance()].PushBack(Signature(std::string(name),type,nullptr,size,value));
	};
}