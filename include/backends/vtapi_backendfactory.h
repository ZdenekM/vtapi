/* 
 * File:   vtapi_backendfactory.h
 * Author: vojca
 *
 * Created on May 7, 2013, 1:02 PM
 */

#ifndef VTAPI_BACKENDFACTORY_H
#define	VTAPI_BACKENDFACTORY_H

#include "vtapi_connection.h"
#include "vtapi_typemanager.h"
#include "vtapi_querybuilder.h"
#include "vtapi_resultset.h"
#include "vtapi_libloader.h"

namespace vtapi {
 
class BackendFactory;
extern BackendFactory g_BackendFactory;

/**
 * @brief Factory for creating objects of backend-specific polymorphic classes
 *
 * Class needs to be initialized with initialize() function before using it.
 * It creates objects of these five classes:
 * - @ref Connection
 *      communication with backend
 * - @ref TypeManager
 *      registering and managing data types
 * - @ref QueryBuilder
 *      building SQL queries
 * - @ref ResultSet
 *      accessing retrieved values
 * - @ref LibLoader
 *      loading library functions
 */
class BackendFactory {
public:

    backend_t backend;        /**< backend type */

    /**
     * Initializes factory with given backend type
     * @param backendType backend type
     * @return success
     */
    bool initialize(const string& backendType = "");

    /**
     * Creates object of class @ref Connection
     * @param fmap library functions address book
     * @param connectionInfo connection string or database folder
     * @param logger message logging object
     * @return NULL if factory is uninitialized, connection object otherwise
     */
    Connection* createConnection(fmap_t *fmap, const string& connectionInfo, Logger *logger);

    /**
     * Creates object of class @ref TypeManager
     * @param fmap library functions address book
     * @param connection connection object
     * @param logger message logging object
     * @return NULL if factory is uninitialized, data type managing object otherwise
     */
    TypeManager* createTypeManager(fmap_t *fmap, Connection *connection, Logger *logger);

    /**
     * Creates object of class @ref QueryBuilder
     * @param fmap library functions address book
     * @param connection connection object
     * @param logger message logging object
     * @param initString initializing string (query or table)
     * @see Query
     * @return NULL if factory is uninitialized, query building object otherwise
     */
    QueryBuilder* createQueryBuilder(fmap_t *fmap, Connection *connection, Logger *logger, const string& initString);

    /**
     * Creates object of class @ref ResultSet
     * @param fmap library functions address book
     * @param typeManager data type managing object
     * @param logger message logging object
     * @return NULL if factory is uninitialized, result set object otherwise
     */
    ResultSet* createResultSet(fmap_t *fmap, TypeManager *typeManager, Logger *logger);

    /**
     * Creates object of class @ref LibLoader
     * @return NULL if factory is uninitialized, library loading object otherwise
     */
    LibLoader* createLibLoader(Logger *logger);
};

} // namespace vtapi

#endif	/* VTAPI_BACKENDFACTORY_H */
