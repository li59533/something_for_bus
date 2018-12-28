using System;
using System.Collections;

namespace $rootnamespace$
{
    /**
     * The delegate used during the traversal of the items in the
     * composite tree structure
     */
    public delegate void Enumgprs_ATCallback(Igprs_AT child);

    /**
     * The interface that defines the elements that make up the
     * composite tree structure
     */
    public interface Igprs_AT
    {
        /**
         * Example of a member function that may be performed on either a
         * composite or component node.
         * TODO: Rename and implement operations in the Composite and
         * Component classes
         */
        void MemberFunction();

        /**
         * Example of a numeric property that may be get or set on either a
         * composite or component node.
         */
        int NumberProperty
        {
            get;
            set;
        }

        /**
         * Adds a new child to the node
         * 
         * @param child  A new child to be added to the child collection
         * 
         * @return	The number of children owned by this object
         */
        int AddChild(Igprs_AT child);

        /**
         * Removes a specific child from the node
         * 
         * @param child  The child object to be removed from the child
         *               collection
         * 
         * @return	The number of children owned by this object
         */
        int RemoveChild(Igprs_AT child);

        /**
         * Property to return the enumerator for the node's immediate 
         * children.
         * 
         * @returns The enumerator for the child collection
         */
        IEnumerator Children
        {
            get;
        }

        /**
         * Traverses the immediate children of the node and sends them to 
         * the caller via the Enumgprs_ATCallback delegate
         * 
         * @param callback A handler for the Enumgprs_ATCallback
         *                 delegate
         */
        void EnumChildren(Enumgprs_ATCallback callback);

        /**
         * Recursively traverses all children underneath the node and
         * sends them to the caller via the Enumgprs_ATCallback
         * delegate.
         * 
         * @param callback A handler for the Enumgprs_ATCallback
         *                 delegate
         */
        void EnumDescendants(Enumgprs_ATCallback callback);
    }

    /**
     * The component class that implements the Igprs_AT 
     * interface.  Objects of this type are considered leaves in the
     * tree and may NOT have children.
     */
    public class gprs_ATComponent : Igprs_AT
    {
        // example number property member
        private int _NumberPropertyValue;

#region Igprs_AT implementation

        /**
         * Example member function implementation
         */
        public void MemberFunction()
        {
            // TODO: Add code to implement the member function
        }

        /**
         * Implementation of the NumberProperty property
         */
        public int NumberProperty
        {
            get { return _NumberPropertyValue; }
            set { _NumberPropertyValue = value; }
        }

        /**
         * AddChild has no implementation in the component class
         */
        public int AddChild(Igprs_AT child)
        {
            return 0;
        }

        /**
         * RemoveChild has no implementation in the component class
         */
        public int RemoveChild(Igprs_AT child)
        {
            return 0;
        }

        /**
         * A component has no children, so return null
         */
        public IEnumerator Children
        {
            get { return null;	}
        }

        /**
         * Because a component has no children, this function requires no
         * implementation
         */
        public void EnumChildren(Enumgprs_ATCallback callback) { }

        /**
         * Because a component has no children, this function requires no
         * implementation
         */
        public void EnumDescendants(Enumgprs_ATCallback callback) { }

#endregion
    }

    /**
     * The composite class that implements the Igprs_AT
     * interface.  Objects of this type are considered nodes in the 
     * tree and may have children.
     */
    public class gprs_ATComposite : Igprs_AT
    {
        // ArrayList of subordinate (child) nodes
        protected ArrayList _subordinates;

#region Composite implementation

        /**
         * Default constructor
         */
        public gprs_ATComposite()
        {
            _subordinates = new ArrayList();
        }

        /**
         * Constructor
         * 
         * @param capacity Allows for preallocation of an expected 
         *                 number of children
         */
        public gprs_ATComposite(int capacity)
        {
            // create the child array list
            _subordinates = new ArrayList(capacity);
        }

#endregion

#region Igprs_AT implementation

        /**
         * Example member function implementation.  Simply forwards
         * the call to the child objects.
         */
        public void MemberFunction()
        {
            // traverse the children
            foreach (Igprs_AT m in _subordinates)
            {
                // call the function on each child
                m.MemberFunction();
            }
        }

        /**
         * Example number property implementation.  Simply gets the number 
         * property from each child object and adds them.
         * 
         * @return The sum of all numbers contained in the leaves under 
         *         this node in the composite tree.
         */
        public int NumberProperty
        {
            get
            {
                int sum = 0;
                // traverse the children
                foreach (Igprs_AT m in _subordinates)
                {
                    // sum their values
                    sum += m.NumberProperty;
                }
                return sum;
            }
            set { }
        }

        /**
         * Adds a new child to the node
         * 
         * @param child A new child to be added to the child collection
         * 
         * @return The number of children owned by this object
         */
        public int AddChild(Igprs_AT child)
        {
            return _subordinates.Add(child);
        }

        /**
         * Removes a specific child from the node
         * 
         * @param child The child object to be removed from the child
         *              collection
         * @return The number of children owned by this object
         */
        public int RemoveChild(Igprs_AT child)
        {
            _subordinates.Remove(child);
            return _subordinates.Count;
        }

        /**
         * Property to return the enumerator for the node's immediate 
         * children.
         * 
         * @returns The enumerator for the child collection
         */
        public IEnumerator Children
        {
            get
            {
                return _subordinates.GetEnumerator();
            }
        }

        /**
         * Traverses the immediate children of the node and sends them to 
         * the caller via the Enumgprs_ATCallback delegate
         * 
         * @param callback A handler for the Enumgprs_ATCallback
         *                 delegate
         */
        public void EnumChildren(Enumgprs_ATCallback callback)
        {
            // make sure the delegate isn't null
            if (callback != null)
            {
                // traverse the children
                foreach (Igprs_AT m in _subordinates)
                {
                    // callback the reference to each one
                    callback(m);
                }
            }
        }

        /**
         * Recursively traverses all children underneath the node and
         * sends them to the caller via the Enumgprs_ATCallback
         * delegate.
         * 
         * @param callback A handler for the Enumgprs_ATCallback
         *                 delegate
         */
        public void EnumDescendants(Enumgprs_ATCallback callback)
        {
            // make sure the delegate isn't null
            if (callback != null)
            {
                // traverse the children
                foreach (Igprs_AT m in _subordinates)
                {
                    // have the current child call back all of it's children
                    m.EnumDescendants(callback);
                    // callback the reference to the current child
                    callback(m);
                }
            }
        }

#endregion
    }
}
