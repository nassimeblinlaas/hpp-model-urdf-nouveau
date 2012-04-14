// Copyright (C) 2012 by Antonio El Khoury.
//
// This file is part of the hpp-model-urdf.
//
// hpp-model-urdf is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// hpp-model-urdf is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-model-urdf.  If not, see <http://www.gnu.org/licenses/>.


/**
 * \brief Declaration of SRDF Parser.
 */

#ifndef HPP_MODEL_SRDF_PARSER
# define HPP_MODEL_SRDF_PARSER

# include <string>
# include <map>

# include <srdf/model.h>

# include <hpp/model/body.hh>
# include <hpp/model/humanoid-robot.hh>

namespace hpp
{
  namespace model
  {
    namespace srdf
    {
      /// \brief Parse an SRDF file to add semantic information
      /// (special configurations, collision pairs) to
      /// an existing hpp::model::HumanoidRobotShPtr.
      class Parser
      {
      public:
	typedef std::pair<std::string, std::string> CollisionPairType;
	typedef std::vector<CollisionPairType> CollisionPairsType;

	typedef std::vector<CkwsJointShPtr> JointPtrsType;
	typedef std::vector<CkcdObjectShPtr> ObjectPtrsType;

	typedef hpp::model::Body BodyType;
	typedef hpp::model::BodyShPtr BodyPtrType;
	typedef hpp::model::HumanoidRobotShPtr RobotPtrType;

	/// \brief Default constructor.
	explicit Parser ();
	/// \brief Destructor.
	virtual ~Parser ();

	/// Display in output stream list of disabled collision pairs.
	void
	displayDisabledCollisionPairs (std::ostream& os);

	/// Display in output stream list of added collision pairs.
	void
	displayAddedCollisionPairs (std::ostream& os);

	/// \brief Parse an URDF file and add semantic information to
	/// humanoid robot.
	///
	/// The URDF and SRDF file location must use the resource
	/// retriever format.
	///
	/// For instance, the following strings are allowed:
	/// - package://myPackage/robot.urdf
	/// - file:///tmp/robot.urdf
	/// - http://mywebsite.com/robot.urdf
	///
	/// See resource_retriever documentation for more information.
	///
	/// \param resourceName resource name using the
	/// resource_retriever format.
	///
	/// \param robotResourceName URDF resource name
	/// \param semanticResourceName SRDF resource name
	void
	parse (const std::string& robotResourceName,
	       const std::string& semanticResourceName,
	       RobotPtrType& robot);

	/// \brief Parse an SRDF sent as a stream and add semantic
	/// information to humanoid robot.
	///
	/// \param robotDescription URDF stream
	/// \param semanticDescription SRDF stream
	void
	parseStream (const std::string& robotDescription,
		     const std::string& semanticDescription,
		     RobotPtrType& robot);

      protected:
	/// \brief Add collision pairs to robot.
	void
	addCollisionPairs ();

	/// \brief Check if given body pair is disabled.
	bool
	isCollisionPairDisabled (const std::string& bodyName_1,
				 const std::string& bodyName_2);

	/// \brief Check if given body pair has been already been
	/// added.
	bool
	isCollisionPairAdded (const std::string& bodyName_1,
			      const std::string& bodyName_2);

      private:
	::urdf::Model urdfModel_;
	::srdf::Model srdfModel_;
	RobotPtrType robot_;
	CollisionPairsType colPairs_;

      }; // class Parser

    } // end of namespace srdf.
  } // end of namespace model.
} // end of namespace hpp.

#endif // HPP_MODEL_SRDF_PARSER
