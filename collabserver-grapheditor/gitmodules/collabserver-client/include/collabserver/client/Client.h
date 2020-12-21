#pragma once

#include "collabserver/datatypes/collabdata/CollabData.h"
#include "collabserver/datatypes/collabdata/CollabDataOperation.h"
#include "collabserver/datatypes/collabdata/CollabDataOperationObserver.h"

namespace collabserver {

/*
 * \brief
 * End user client interface.
 *
 * Module to connect a remote CollabServer and work on a CollabData.
 * Only one CollabData can be active at the same time.
 */
class Client : CollabDataOperationObserver {
   private:
    CollabData* _data = nullptr;
    unsigned int _dataID = 0;
    unsigned int _userID = 0;

   public:
    Client();
    ~Client();

   public:
    /**
     * Try to open connection with the remote server.
     * Block until server responds.
     *
     * \todo
     * There is no timeout for now.
     * This block indefinitely if no server respond.
     *
     * \param ip        IP of the remove server.
     * \param port      Port of the remove server.
     * \return True if successfully connected, otherwise, return false
     */
    bool connect(const char* ip, const int port);

    /**
     * Stop connection with remote server.
     * Block until server responds.
     * Leave data if any data is currently loaded.
     *
     * \return True if successfully disconnected, otherwise, return false
     */
    bool disconnect();

    /**
     * Creates new collaborative data on server and join it.
     * Do nothing if another data is already loaded (And returns false).
     * This methods wait and block until server answers.
     * Block until server responds.
     *
     * \warning
     * Data is your actual implementation of CollabData.
     * Don't do any operations on it before calling this function,
     * otherwise, these changes won't be broadcasted to others.
     *
     * \param data Pointer to your local data instance.
     * \return True if successfully created, otherwise, return false.
     */
    bool createData(CollabData* data);

    /**
     * Join a collab data already started on server side.
     * Data ID is attributed by the server. You may get it from its owner.
     * Block until server responds.
     *
     * \warning
     * Data is your actual implementation of CollabData.
     * Don't do any operations on it before calling this function,
     * otherwise, these changes won't be broadcasted to others.
     *
     * \param data Pointer to your local data instance.
     * \param dataID Unique ID of the data on server.
     * \return True if successfully joined, otherwise, return false.
     */
    bool joinData(CollabData* data, unsigned int dataID);

    /**
     * Leave the current data collaboration.
     * Does nothing if no data already loaded.
     * Block until server responds.
     *
     * \return True if successfully left, otherwise, return false.
     */
    bool leaveData();

    // ---------------------------------------------------------------------
    // Getters / Setters
    // ---------------------------------------------------------------------

   public:
    /**
     * Get the current collab data ID.
     * This is the common ID to identify the data on the collab server.
     *
     * \return ID of the data in collab server.
     */
    unsigned int getDataID() const { return _dataID; }

    /**
     * Get the current user ID as registered in CollabServer
     *
     * \return ID of the user
     */
    unsigned int getUserID() const { return _userID; }

    /**
     * Get pointer to the current data you are collaborating on.
     * Returns null if no data loaded.
     *
     * \return Pointer to the data.
     */
    CollabData* getData() { return _data; }

    /**
     * Check whether client is currently connected to a CollabServer.
     *
     * \return True if connected, otherwise, return false.
     */
    bool isConnected() const { return _userID != 0; }

    /**
     * Check whether a CollabServer data has been loaded.
     * If no data loaded, this means no collaboration is ongoing.
     *
     * \return True if data loaded, otherwise, return false.
     */
    bool isDataLoaded() const { return _dataID != 0; }

    /**
     * You just found the terrible easter egg.
     * Ask the server if you are ugly and wait for his answer.
     * If you are not connected yet, returns true (You are obviously ugly
     * if you asking the server before being connected with him!)
     * Block until server responds.
     *
     * \return True if you are ugly (According to the server).
     */
    bool isUgly() const;

    // ---------------------------------------------------------------------
    // OperationObserver overrides
    // ---------------------------------------------------------------------

   private:
    /**
     * On operation applied locally, broadcast it to others.
     * This is an internal method (Private).
     *
     * \param op Operation to broadcast.
     */
    void onOperation(const CollabDataOperation& op) override;
};

}  // namespace collab

